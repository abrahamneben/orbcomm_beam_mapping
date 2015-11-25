# written by abraham on aug 24


def dyear2date(dyear):

	year = int(dyear)

	month_lengths = [31,28,31,30,31,30,31,31,30,31,30,31]
	days_before_months = [0,31,59,90,120,151,181,212,243,273,304,334]

	days_into_year_f = (dyear-year)*365
	days_into_year_i = int(days_into_year_f)

	for i in range(12):
		if days_before_months[i] < days_into_year_f < (days_before_months[i]+month_lengths[i]):
			month = i+1
			break

	date = days_into_year_i - days_before_months[month-1]
	hours_f = (days_into_year_f-days_into_year_i)*24
	hours_i = int(hours_f)
	minutes_f = (hours_f-hours_i)*60
	minutes_i = int(minutes_f)
	seconds_i = int((minutes_f-minutes_i)*60)

	return "%02d/%02d/%d %02d:%02d:%02d" % (month,date,year,hours_i,minutes_i,seconds_i)
