import atexit
import sqlite3

import DAO
import DTO


class _Repository:
    def __init__(self):
        self._conn = sqlite3.connect("moncafe.db")
        self.employees = DAO.Employees(self._conn)
        self.suppliers = DAO.Suppliers(self._conn)
        self.coffee_stands = DAO.Coffee_stands(self._conn)
        self.activities = DAO.Activities(self._conn)
        self.products = DAO.Products(self._conn)

    def _close(self):
        self._conn.commit()
        self._conn.close()


    def create_tables(self, path):
        self._conn.executescript("""
                CREATE TABLE Employees(
                    id INTEGER PRIMARY KEY, 
                    name TEXT NOT NULL,
                    salary REAL NOT NULL,
                    coffee_stand INTEGER REFERENCES Coffee_stands(id)        
                 );

                 CREATE TABLE Suppliers(
                    id INTEGER PRIMARY KEY,
                    name TEXT NOT NULL,
                    contact_information TEXT
                 );

                 CREATE TABLE Products(
                    id INTEGER PRIMARY KEY,
                    description TEXT NOT NULL,
                    price REAL NOT NULL,
                    quantity INTEGER NOT NULL
                 );

                 CREATE TABLE Coffee_stands(
                    id INTEGER PRIMARY KEY,
                    location TEXT NOT NULL,
                    number_of_employees INTEGER
                 );

                 CREATE TABLE Activities(
                    product_id INTEGER REFERENCES Products(id),
                    quantity INTEGER NOT NULL,
                    activator_id INTEGER NOT NULL,
                    date DATE NOT NULL
                 );
            """)

        text = open(path).readlines()
        for line in text:
            line = line.split(', ')
            for element in range(0,line.__len__()):
                line[element] = str(line[element]).replace("\n", '')

            if (line[0] == "C"):
                coffee_stand = DTO.Coffee_stand(int(line[1]), line[2], int(line[3]))
                self.coffee_stands.insert(coffee_stand)
            elif (line[0] == "S"):
                supplier = DTO.Supplier(int(line[1]), line[2], line[3])
                self.suppliers.insert(supplier)
            elif (line[0] == "E"):
                employee = DTO.Employee(int(line[1]), line[2], float(line[3]), int(line[4]))
                self.employees.insert(employee)
            elif (line[0] == "P"):
                product = DTO.Product(int(line[1]), line[2], float(line[3]), 0)
                self.products.insert(product)

    def InsertActivities (self, path):
        text = open(path).readlines()
        for line in text:
            line.replace(' ', '')  ## remove all whitespaces
            line = line.split(',')
            product_id = int(line[0])
            units_quantity = int(line[1])
            supplier_id = int(line[2])
            date_string = line[3]
            cur = self._conn.cursor()
            q = self.products.find(product_id);
            if units_quantity > 0:  ## suply
                a = DTO.Activity(product_id, units_quantity, supplier_id, date_string)
                self.activities.insert(a)
                self.products.update_quantity(units_quantity, product_id)
            elif int(q) + units_quantity >= 0:  ## sell legal
                a = DTO.Activity(product_id, units_quantity, supplier_id, date_string)
                self.activities.insert(a)
                self.products.update_quantity(units_quantity, product_id)

    def findAll(self, table):
        if(table == "Products"):
            return self.products.findAll()
        elif(table == "Employees"):
            return self.employees.findAll()
        elif (table == "Coffee_stands"):
            return self.coffee_stands.findAll()
        elif (table == "Suppliers"):
            return self.suppliers.findAll()
        elif (table == "Activities"):
            return self.activities.findAll()

    def getActivitiesByDate (self):
        return self.activities.getActivitiesByDate()

    def getNumberOfActivities(self):
        return self.activities.getNumberOfActivities()

    def getEmployeesReport(self):
        c = self._conn.cursor()
        c.execute( """SELECT DISTINCT name,salary,location, sum (IFNULL(Activities.quantity,0) * -1 * IFNULL(Products.price,
                0)) FROM (((Employees Left OUTER JOIN Coffee_stands ON Coffee_stands.id = Employees.coffee_stand) LEFT OUTER 
                JOIN Activities ON Employees.id = Activities.activator_id) LEFT OUTER JOIN Products ON Products.id = 
                Activities.product_id) GROUP BY Employees.id ORDER BY name ASC""")
        return c.fetchall()

    def getActivitiesReport(self):
        c = self._conn.cursor()
        c.execute("""SELECT Activities.date, description, Activities.quantity,Employees.name, Suppliers.name FROM (Activities JOIN Products ON 
               product_id = Products.id) LEFT OUTER JOIN Suppliers ON activator_id = Suppliers.id LEFT OUTER JOIN 
               Employees ON activator_id = Employees.id ORDER BY date ASC""")
        return c.fetchall()


# the repository singleton
repo = _Repository()
atexit.register(repo._close)
