const mysql = require('mysql');
const config = require('config');

const {host, port, user, password, database} = config.database;
const connection = SQL.createConnection({host, port, user, password, database})

module.exports = connection;