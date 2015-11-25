from datetime import datetime,timedelta

class templog:

	def __init__(self):
		f_temps = open('beamformer_temp.log','r')
		datetimes_and_temps_raw = f_temps.readlines()
		f_temps.close()

		self.dt_start = self.todatetime(*(datetimes_and_temps_raw[0].split(',')[0].split()))
		self.dt_end   = self.todatetime(*(datetimes_and_temps_raw[-1].split(',')[0].split()))
		#dt = (self.dt_end - self.dt_start).total_seconds() # only works in python >2.7
		self.total_seconds = self.total_seconds_of_timedelta(self.dt_end - self.dt_start)
		self.temps = [float(line.split(',')[1]) for line in datetimes_and_temps_raw]
		self.num_temps = len(self.temps)
		
	def total_seconds_of_timedelta(self,td):
		return td.seconds + td.days * 24 * 3600

	def todatetime(self,date_str,time_str):
		#return datetime.strptime(datetime_str, "%m/%d/%Y %H:%M:%S") # only works in python >2.5
		[month,day,year] = map(int,date_str.split('/'))
		[hour,minute,second] = map(int,time_str.split(':'))
		return datetime(year,month,day,hour,minute,second)

	def get_temp_for_datetime_str(self,date_str,time_str):
		desired_dt = self.todatetime(date_str,time_str)
		seconds_since_start = self.total_seconds_of_timedelta(desired_dt-self.dt_start)
		dt_index = int(float(seconds_since_start)/self.total_seconds*self.num_temps)
		
		return self.temps[dt_index]*9./5+32,seconds_since_start/3600.

