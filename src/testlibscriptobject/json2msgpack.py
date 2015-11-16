import sys
import json
import umsgpack

with open(sys.argv[1], "rt") as f:
    obj = json.load(f)

with open(sys.argv[2], "wb") as f:
    umsgpack.pack(obj, f)

