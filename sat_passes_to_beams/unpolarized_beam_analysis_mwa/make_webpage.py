pointings=['W04S01','W03S00','W02S00','W01S00','Zenith','E01S00','E02S00','E03S00','E04S01']

f=open('phase4_unpolarized_analysis.html','w')
f.write('''
<html>
<head>
<style>
</style>
<title>Phase 4 Unpolarized Analysis</title>
</head>
<body>
''')

f.write('<table>')
for pointing in pointings:
	f.write('<tr><td><img src="'+pointing+'_map.png"/></td><td><img src="'+pointing+'_EW_E_plane.png"/></td><td><img src="'+pointing+'_EW_H_plane.png"/></td><td><img src="'+pointing+'_NS_E_plane.png"/></td><td><img src="'+pointing+'_NS_H_plane.png"/></td></tr>')

f.write('''
</table>
</body>
</html>
''')
f.close()
