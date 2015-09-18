var config = require(__dirname + '/plotly-config.json'),
    username = config['user'],
    apikey = config['apikey'],
    token = config['token'],
    Plotly = require('plotly')(username, apikey)

var debug = require('debug')('plotly-plugin')
var _ = require('lodash')


// build a data object - see https://plot.ly/api/rest/docs for information
var data = {
    'x': [] // empty arrays since we will be streaming our data to into these arrays
        ,
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

// build you layout and file options
var layout = {
    "filename": "streamSimpleSensor",
    "fileopt": "overwrite",
    "layout": {
        "title": "streaming sensor data"
    },
    "world_readable": true
}

/*
 * Call plotly.plot to set the file up.
 * If you have included a streaming token
 * you should get a "All Streams Go!" message
 */

var plotlystream
var i = 0



function init() {
    Plotly.plot(data, layout, function(err, resp) {
        debug(resp)
        if (err) return console.log("ERROR", err)
        plotlystream = Plotly.stream(token, function() {})
    })
}

function process(m) {
    if (!_.isUndefined(plotlystream)) {
        var dta = {
            x: i,
            y: m.temp_value_C
        }
        var payload = JSON.stringify(dta) + '\n'
        plotlystream.write(payload);
        i++;
    }
}

module.exports = {
    init: init,
    process: process
}
