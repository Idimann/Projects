const express = require('express')
const app = express()
const port = 3000

app.get('/', (_, res) => {
  res.send('<div> Hello world! </div>')
})

app.put('/', (_, res) => {
  res.send('<div> Hello world! </div>')
})

app.listen(port, () => {
  console.log(`Express listening on port ${port}`)
})

