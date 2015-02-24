#
# Regular cron jobs for the osrm-backend package
#
0 4	* * *	root	[ -x /usr/bin/osrm-backend_maintenance ] && /usr/bin/osrm-backend_maintenance
