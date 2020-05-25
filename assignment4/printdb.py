from Repo import _Repository


def printdb():
    repo = _Repository()
    print("Activities")
    q = repo.getActivitiesByDate()
    for tup in q:
        print(tup)
    print("Coffee stands")
    q = repo.findAll("Coffee_stands")
    for tup in q:
        print(tup)
    print("Employees")
    q = repo.findAll("Employees")
    for tup in q:
        print(tup)
    print("Products")
    q = repo.findAll("Products")
    for tup in q:
        print(tup)
    print("Suppliers")
    q = repo.findAll("Suppliers")
    for tup in q:
        print(tup)

    print("\nEmployees report")
    q = repo.getEmployeesReport()
    for tup in q:
        tup1 = str(tup).replace(")", "")
        tup1 = tup1.replace("(", "")
        tup1 = tup1.replace(", ", " ")
        tup1 = tup1.replace("'", "")
        print(tup1)

    q = repo.getNumberOfActivities()
    if int(q) > 0:
        print("\nActivities")
        q = repo.getActivitiesReport()
        for tup in q:
            print(tup)


def main():
    printdb()


if __name__ == "__main__":
    main()
