const express = require('express')
const bodyParser = require('body-parser')
const db = require('./queries')

const app = express()
const port = 5070

app.use(bodyParser.json())
app.use(
  bodyParser.urlencoded({
    extended: true,
  })
)


app.get('/', (request, response) => {
    response.json({ info: 'Node.js, Express, and Postgres API' })
})


app.get('/consumptions', db.getConsumptions);


app.get('/test', (req, res) => {
  res.status(200).send({
    "main":{
      "test" : 2
    }
  });
});


app.post('/consumptions', db.createConsumption);

app.listen(port, () => {
    console.log(`App running on port ${port}.`)
})