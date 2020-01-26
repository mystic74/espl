const express = require('express')
const app = express()
const port = 3000
var { PythonShell } = require('python-shell');
var bodyParse = require('body-parser')
app.use(bodyParse.urlencoded({extended:true}));
//app.post('/sendmail', (req, res) => res.send('Hello World!'))
app.post('/sendmail', (req, res) => {
    console.log('Entering lambda function')
    var options = {
    mode: 'text',
    pythonPath: '/usr/bin/python2.7',
    pythonOptions: ['-u'],
    scriptPath: '/users/studs/bsc/2019/ronento/espl/lab10',
    //args: ['val1', 'val2', 'val3']
    args: [req.body.fname,
           req.body.mail,
           req.body.fname + " with " + req.body.mail + " has send you " + req.body.msg] //these are the arguments that the python script will receive
    };

    //console.log('sending to my_script.py at users/studs/bsc/2019/ronento/espl/lab10')
    PythonShell.run('my_script.py', options, function (err, results) {
    if (err) throw err;
    // results is an array consisting of messages collected during execution
    console.log('results: %j', results);
    });
})

app.listen(port, () => console.log(`Server listening on port ${port}!`))
