from plotly.offline import plot
import plotly.graph_objs as go

#Read in expression levels with genes
def readInData(fileName, RS3Vals, RS4Vals):
    print("Reading in data")
    f = open(fileName, 'r')
    
    #Skip the header line
    line = f.readline()
    
    #Read each line
    line = f.readline()

    while line:
        
        numStr = line.split()[1]
        RS3Vals.append(float(numStr))
        
        numStr = line.split()[2]
        RS4Vals.append(float(numStr))

        line = f.readline()

    f.close()

#sample heatmap
def heatMap(RS3, RS4):
    trace = go.Heatmap(z=[RS3, RS4], y = ["RS3", "RS4"])
    data = [trace]
    plot(data, filename="sample.html")

#------ Start of execution --------
RS3 = []
RS4 = []
readInData("overlap.csv", RS3, RS4)

heatMap(RS3, RS4)
