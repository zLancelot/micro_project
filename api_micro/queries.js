const Pool = require('pg').Pool
const pool = new Pool({
  user: 'me',
  host: 'localhost',
  database: 'api',
  password: 'password',
  port: 5432,
})



const getConsumptions = (request, response) => {
    pool.query('SELECT * FROM time_consumption_by_date', (error, results) => {
      if (error) {
        throw error
      }
      response.status(200).json(results.rows)
    })
  }


const getConsumptionByDate = (req, res) => {
  const { date } = request.body;

  pool.query('select * FROM time_consumption_by_date WHERE date = ($1)', [date], (error, result) => {
    if (error) {
      throw error
    }
    res.status(200).send(result.rows);
  })
}

  const createConsumption = (request, response) => {
    const { consumption } = request.body
  
    pool.query('INSERT INTO time_consumption_by_date (consumption_time) VALUES ($1)', [consumption], (error, result) => {
      if (error) {
        throw error
      }
      response.status(201).send(`Consumption Time added with ID: ${result.insertId}`)
    })
  }

module.exports = {getConsumptions, createConsumption}