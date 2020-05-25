# Data Access Objects:
# All of these are meant to be singletons
class Employees:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, employee):
        self._conn.execute("INSERT INTO Employees VALUES(?,?,?,?)", [employee.id, employee.name, employee.salary,
                                                                     employee.coffee_stand])
        self._conn.commit()

    def findAll(self):
        c = self._conn.cursor()
        c.execute("SELECT * FROM Employees")
        return c.fetchall()


class Suppliers:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, supplier):
        self._conn.execute("INSERT INTO Suppliers VALUES(?,?,?)",
                           [supplier.id, supplier.name, supplier.contact_information])
        self._conn.commit()

    def findAll(self):
        c = self._conn.cursor()
        c.execute("SELECT * FROM Suppliers")
        return c.fetchall()


class Products:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, product):
        self._conn.execute("INSERT INTO Products VALUES(?,?,?,?)",
                           [product.id, product.description, product.price, product.quantity])
        self._conn.commit()

    def find(self, product_id):
        c = self._conn.cursor()
        c.execute("""SELECT quantity FROM Products WHERE id = ?""", [product_id])
        q = c.fetchone()[0]
        return q

    def findAll(self):
        c = self._conn.cursor()
        c.execute("SELECT * FROM Products")
        return c.fetchall()

    def update_quantity(self, units_quantity, product_id):
        c = self._conn.cursor()
        c.execute("""UPDATE Products SET quantity = quantity + ? WHERE id = ?""",
                  [int(units_quantity), int(product_id)])
        self._conn.commit()


class Coffee_stands:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, coffee_stand):
        self._conn.execute("INSERT INTO Coffee_stands VALUES(?,?,?)",
                           [coffee_stand.id, coffee_stand.location, coffee_stand.number_of_employees])
        self._conn.commit()

    def findAll(self):
        c = self._conn.cursor()
        c.execute("SELECT * FROM coffee_stands")
        return c.fetchall()


class Activities:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, activity):
        p1 = activity.product_id
        p2 = activity.quantity
        p3 = activity.activator_id
        p4 = activity.date
        c = self._conn.cursor()
        c.execute("INSERT INTO Activities VALUES(?,?,?,?)", [int(p1), int(p2), int(p3), str(p4)])
        self._conn.commit()

    def findAll(self):
        c = self._conn.cursor()
        c.execute("SELECT * FROM Activities")
        return c.fetchall()

    def getActivitiesByDate(self):
        c = self._conn.cursor()
        c.execute("SELECT * FROM Activities order by date ASC")
        return c.fetchall()

    def getNumberOfActivities(self):
        c = self._conn.cursor()
        c.execute("SELECT count(*) FROM Activities")
        return c.fetchone()[0]
