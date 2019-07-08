import json
import matplotlib.pyplot as plt


print("STARTING")
print('LOADING FILE')
json_file = open("../sim_data/test/small_true2.json", "r")
print('LOADING COMPLETE')
print('PARSING FILE')
data = json.load(json_file)
print('PARSING COMPLETE')

plot_style = int(input("Enter 0 to plot all data, enter 1 for manual nav or 2 for sequential nav : "))

def plot_particle(pid):

	p_Xvals = []
	p_Yvals = []

	for f in data["FRAME_DATA"]:
		for s in f["SUBFRAMES"]:
			p = s["particles"][pid]

			p_dta = p["p_data"]

			x = p_dta["p"]["x"]
			y = p_dta["p"]["y"]


			p_Xvals.append(x)
			p_Yvals.append(y)
			
			print(str(pid) + ": " + str(f["f-num"]) + " : " + str(s["sub_frame"]) + " : " + str(p["id"]) + "x: " + 
				  str(p_dta["p"]["x"])+ "  :  " + "y: " +  str(p_dta["p"]["y"]) + " r: " + str(p_dta["r"]))

	plt.axes().set_aspect("equal")
	plt.xlim(0, data["WINDOW_DATA"]["width"])
	plt.ylim(0, data["WINDOW_DATA"]["height"])
	plt.gca().invert_yaxis()
	plt.plot(p_Xvals, p_Yvals, color = "red", zorder = 1)
	plt.scatter(p_Xvals, p_Yvals, s = 5, color = "blue", zorder = 2)
	

	p_Xvals = []
	p_Yvals = []

def plot_all():

	for i in range(0, int(data["PARTICLE_COUNT"])):
		plot_particle(i)



if(plot_style == 0):

	plot_all()
	plt.show()


if(plot_style == 1):
	while(1):
		print("Choose a particle id between 0, and " + str(data["PARTICLE_COUNT"]))
		pid = int(input())
		plot_particle(pid)

		plt.show()


if(plot_style == 2):
	for x in range(data["PARTICLE_COUNT"]):

		plot_particle(x)
		plt.show()



