#!/usr/bin/env python

import inkex
import sys

# for more power
import simpletransform
import cubicsuperpath


class TemplateEffect(inkex.Effect):
    def __init__(self):
        # Call base class construtor.
        inkex.Effect.__init__(self)
        
  
        

    def effect(self):
        
        #Loop through all the selected items in Inkscape
        for node in self.selected.iteritems():
            
            #Create the string variable which will hold the formatted data (note that '\n' defines a line break)
            output_all = output_nodes = ""
                    
            #Iterate through all the selected objects in Inkscape
            for id, node in self.selected.iteritems():
                #Check if the node is a path ( "svg:path" node in XML ) 
                if node.tag == inkex.addNS('path','svg'):
                    #Create the string variables which will hold the formatted data
                    output_all += ""
                    output_nodes += ""
                    
                    # bake (or fuse) transform
                    simpletransform.fuseTransform(node)
                    #turn into cubicsuperpath
                    d = node.get('d')
                    p = cubicsuperpath.parsePath(d)
                    for subpath in p: # there may be several paths joined together (e.g. holes)
                        for csp in subpath: # groups of three to handle control points.
                            # just the points no control points (handles)
                            output_nodes += str(csp[1][0]) + "," + str(csp[1][1]) + "\n"
                            # all the points
                            output_all += str(csp[0][0]) + "," + str(csp[0][1]) + " "
                            output_all += str(csp[1][0]) + "," + str(csp[1][1])  + " "
                            output_all += str(csp[2][0]) + "," + str(csp[2][1])  + "\n"
                        output_all += ";\n"
                    
            #
            sys.stderr.write("Nodes only (in absolute position):\n%s" % output_nodes)
            sys.stderr.write("\nIncluding handles:\n%s" % output_all)
            sys.stderr.write("\nThe triplets are control point1, node, control point 2.\n")
            

# Create effect instance and apply it.
effect = TemplateEffect()
effect.affect()
