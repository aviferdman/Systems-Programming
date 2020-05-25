import os
import sys

if os.path.exists("moncafe.db"):
    os.remove("moncafe.db")

from Repo import repo


def main(argv):
    repo.create_tables(argv)


if __name__ == '__main__':
    main(sys.argv[1])
