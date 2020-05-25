import sys

from Repo import _Repository
from printdb import printdb

path = sys.argv[1]

repo = _Repository()
repo.InsertActivities (path)

printdb()
