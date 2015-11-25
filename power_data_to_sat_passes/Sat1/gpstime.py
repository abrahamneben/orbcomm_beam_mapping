#!/usr/bin/python

from astropy.time import Time
from datetime import datetime
ut = Time(datetime.utcnow(), scale='utc')
print ut.gps

