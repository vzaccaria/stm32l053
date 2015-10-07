var config = require(__dirname + '/plotly-config.json'),
    username = config['user'],
    apikey = config['apikey'],
    token = config['token'],
    Plotly = require('plotly')(username, apikey)

var debug = require('debug')('plotly-plugin')
var _ = require('lodash')
var $m = require('moment')


function initData(token) {
    return {
        'x': [],
        'y': [],
        'type': 'scatter',
        'mode': 'lines+markers',
        marker: {
            color: "rgba(31, 119, 180, 0.96)"
        },
        line: {
            color: "rgba(31, 119, 180, 0.31)"
        },
        stream: {
            "token": token,
            "maxpoints": 100
        }
    }
}
// build a data object - see https://plot.ly/api/rest/docs for information

// build you layout and file options
var layout = {
    "filename": "streamSimpleSensor",
    "fileopt": "overwrite",
    "layout": {
        "title": "STM32 MEMS sensor data",
        "yaxis": {
            title: "temperature (C)"
        }
    },
    "world_readable": true
}

/*
 * Call plotly.plot to set the file up.
 * If you have included a streaming token
 * you should get a "All Streams Go!" message
 */

var plotlystream
var data
var i = 0


function init() {
    /* Build initialization object */
    data = _.map(config.tokens, initData)

    /* Initialize the library */
    Plotly.plot(data, layout, function(err, resp) {
        debug(resp)
        if (err) {
            console.log("Something went wrong when connecting to plotly:");
            console.log(err)
            return;
        } else {
            console.log("Connection established; you can watch the data stream here:");
            console.log(resp.url);
        }

        plotlystream = _.map(config.tokens, function(token) {
            return Plotly.stream(token, function() {})
        })
    })
}

function process(m) {
    if (!_.isUndefined(plotlystream)) {
        _.map(plotlystream, function(s) {
            var datum = m.temp_value_C
            var dta = {
                x: $m().format('YYYY-MM-DD HH:mm:ss.SS'),
                y: datum
            }
            var payload = JSON.stringify(dta) + '\n'
            s.write(payload);
        })
        i++;
    }
}

module.exports = {
    init: init,
    process: process
}
