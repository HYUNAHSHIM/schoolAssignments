#!/usr/bin/env python3
# -*- coding: utf-8 -*
# sample_python aims to allow seamless integration with lua.
# see examples below

import os
import sys
import pdb  # use pdb.set_trace() for debugging
import code # or use code.interact(local=dict(globals(), **locals()))  for debugging.
import xml.etree.ElementTree as ET
import numpy as np
import math
from PIL import Image 

class Color:
    def __init__(self, R, G, B):
        self.color=np.array([R,G,B]).astype(np.float)

    # Gamma corrects this color.
    # @param gamma the gamma value to use (2.2 is generally used).
    def gammaCorrect(self, gamma):
        inverseGamma = 1.0 / gamma;
        self.color=np.power(self.color, inverseGamma)

    def toUINT8(self):
        return (np.clip(self.color, 0,1)*255).astype(np.uint8)

class Ray:
	light = {} #position, intensity
	light_n = 0

	def add_value(self, viewPoint, viewDir, projNormal, viewUp, projDistance, viewWidth, viewHeight):
		self.viewPoint = viewPoint
		self.viewDir = viewDir
		self.projNormal = projNormal
		self.viewUp = viewUp
		self.projDistance = projDistance
		self.viewWidth = viewWidth
		self.viewHeight = viewHeight

class Object:
	shader = {} #name, type, diffuseColor_c, (specularcolor, exponent)
	shader_n = 0
	surface = {} #type, ref, (center, radius), (minPt, maxPt)
	surface_n = 0

	def sphere(self, n, e, D):
		sur = self.surface[n]

		eq = float(np.dot(D, e-sur['center']))**2 - np.dot(D, D)*(np.dot(e-sur['center'],e-sur['center'])-sur['radius']**2)

		if(eq >=0):
		 	return (-1*np.dot(D, e-sur['center'])-np.sqrt(eq))/np.dot(D,D)

		return math.inf

	def box(self, n, e, ray_direction):
		sur = self.surface[n]

		minPt = sur['minPt']
		maxPt = sur['maxPt']

		txmin = (minPt[0]-e[0])/ray_direction[0]
		txmax = (maxPt[0]-e[0])/ray_direction[0]
		tymin = (minPt[1]-e[1])/ray_direction[1]
		tymax = (maxPt[1]-e[1])/ray_direction[1]
		tzmin = (minPt[2]-e[2])/ray_direction[2]
		tzmax = (maxPt[2]-e[2])/ray_direction[2]
		tmin = txmin
		tmax = txmax

		if(tmin > tmax):
			tmin, tmax = tmax, tmin
		if(tymin > tymax):
			tymin, tymax = tymax, tymin
		if(tzmin >tzmax):
			tzmin, tzmax = tzmax, tzmin

		if((tmin > tymax) or (tymin > tmax)):
			return math.inf
		if(tymin > tmin):
			tmin = tymin
		if(tymax < tmax):
			tmax = tymax

		if((tmin>tzmax) or (tzmin > tmax)):
			return math.inf
		if(tzmin > tmin):
			tmin = tzmin
		if(tzmax < tmax):
			tmax = tzmax

		return tmin

	def shading(self, T, ray, i, j, ob_n, lig_n, S, img, e):
		sur = self.surface[ob_n]
		lig = ray.light[lig_n]

		for k in range(0, self.shader_n):
			if(self.shader[k]['name'] == sur['ref']):
				break
		shade = self.shader[k]

		v = vector_normalize(S-e) * (-1)

		if(sur['type'] == 'Sphere'):
			rt = e + T * (S-e)
			L = vector_normalize(lig['position'] - rt)
			H = vector_normalize(v + L)
			N = vector_normalize(rt - sur['center'])

			if(shade['type'] == 'Phong'):
				result = shade['diffuseColor_c']* lig['intensity'] *max(0, np.dot(N,L)) + shade['specularColor'] * lig['intensity'] * pow(max(0, np.dot(N, H)), shade['exponent'])
			else:
				result = shade['diffuseColor_c'] * lig['intensity'] * max(0, np.dot(N,L))

		else:
			rt = e + T * vector_normalize(S-e)
			p = rt - (sur['minPt'] + sur['maxPt'])/2
			bias = 1.000001
			D = (sur['maxPt'] - sur['minPt'])/2
			
			L = vector_normalize(lig['position'] - rt)
			H = vector_normalize(v + L)
			N = vector_normalize(np.array([int(bias * p[0]/abs(D[0])), int(bias* p[1]/abs(D[1])), int(bias * p[2]/abs(D[2]))]).astype(np.float)) 

			if(shade['type'] == 'Phong'):
				result = shade['diffuseColor_c'] * lig['intensity'] * max(0,np.dot(N,L)) + shade['specularColor'] * lig['intensity'] * pow(max(0, np.dot(N,H)), shade['exponent'])
			else: 
				result = shade['diffuseColor_c'] * lig['intensity'] * max(0, np.dot(N,L))

			
		return result



def vector_normalize(v):
    return v/np.sqrt(np.square(v[0])+np.square(v[1])+np.square(v[2]))

def main():

    tree = ET.parse(sys.argv[1])
    root = tree.getroot()
    ob = Object()
    ray = Ray()

    # set default values
    viewDir=np.array([0,0,-1]).astype(np.float)
    viewUp=np.array([0,1,0]).astype(np.float)
    viewProjNormal=-1*viewDir  # you can safely assume this. (no examples will use shifted perspective camera)
    viewWidth=1.0
    viewHeight=1.0
    projDistance=1.0
    intensity=np.array([1,1,1]).astype(np.float)  # how bright the light is.

    imgSize=np.array(root.findtext('image').split()).astype(np.int)

    for c in root.findall('camera'):
        viewPoint=np.array(c.findtext('viewPoint').split()).astype(np.float)
        viewDir = np.array(c.findtext('viewDir').split()).astype(np.float)
        viewProjNormal = -1*viewDir
        viewUp = np.array(c.findtext('viewUp').split()).astype(np.float)
        projDistance = c.findtext('projDistance')
        if(projDistance == None):
        	projDistance = 1.0
        viewWidth = c.findtext('viewWidth')
        viewHeight = c.findtext('viewHeight')
        ray.add_value(viewPoint, viewDir, viewProjNormal, viewUp, projDistance, viewWidth, viewHeight)

    for c in root.findall('shader'):
    	shader_type=c.get('type')
    	name = c.get('name')
    	diffuseColor_c=np.array(c.findtext('diffuseColor').split()).astype(np.float)
    	dic = {'name' : name, 'type' : shader_type, 'diffuseColor_c': diffuseColor_c}
    	if(shader_type=='Phong'):
    		specularColor=np.array(c.findtext('specularColor').split()).astype(np.float)
    		exponent=float(c.findtext('exponent'))
    		dic['specularColor'] = specularColor
    		dic['exponent'] = exponent
    	ob.shader[ob.shader_n] = dic
    	ob.shader_n = ob.shader_n + 1

    for c in root.findall('surface'):
    	typ = c.get('type')
    	for k in c.findall('shader'):
    		ref = k.get('ref')
    	dic = {'type': typ, 'ref': ref}
    	if(typ == 'Sphere'):
    		center = np.array(c.findtext('center').split()).astype(np.float)
    		radius = float(c.findtext('radius'))
    		dic['center'] = center
    		dic['radius'] = radius
    	if(typ == 'Box'):
    		minPt = np.array(c.findtext('minPt').split()).astype(np.float)
    		maxPt = np.array(c.findtext('maxPt').split()).astype(np.float)
    		dic['minPt'] = minPt
    		dic['maxPt'] = maxPt
    	ob.surface[ob.surface_n] = dic
    	ob.surface_n = ob.surface_n + 1

    for c in root.findall('light'):
    	position = np.array(c.findtext('position').split()).astype(np.float)
    	intensity = np.array(c.findtext('intensity').split()).astype(np.float)
    	dic2 = {'position': position, 'intensity': intensity}
    	ray.light[ray.light_n] = dic2
    	ray.light_n = ray.light_n + 1
    #code.interact(local=dict(globals(), **locals()))  

    # Create an empty image
    channels=3
    img = np.zeros((imgSize[1], imgSize[0], channels), dtype=np.uint8)
    img[:,:]=0

    for j in np.arange(imgSize[1]):#320 가로 
    	for i in np.arange(imgSize[0]):
    		T = 0
    		mint = math.inf
    		minob_n = 0

    		d = float(ray.projDistance)
    		e = ray.viewPoint
    		l = -1*float(ray.viewWidth)/2.0
    		r = float(ray.viewWidth)/2.0
    		b = -1*float(ray.viewHeight)/2.0
    		t = float(ray.viewHeight)/2.0

    		W = vector_normalize(ray.projNormal)
    		U = vector_normalize(np.cross(ray.viewUp, W))
    		V = vector_normalize(np.cross(U, W))

    		u = l + (r-l)*(i+0.5)/imgSize[0]
    		v = b + (t-b)*(j+0.5)/imgSize[1]
    		S = e + u*U + v*V - d*W
    		D = S - e

    		for k in range(ob.surface_n):
    			if(ob.surface[k]['type'] == 'Sphere'):
    				D = S-e
    				T = ob.sphere(k, e, D)
    			if(ob.surface[k]['type'] == 'Box'):
    				ray_direction = vector_normalize(S-e)
    				T = ob.box(k, e, ray_direction)
    			if(T < mint):
    				mint = T
    				minob_n = k

    		#shading
    		color = np.array([0,0,0])
    		if(mint != math.inf):
    			

    			for r in range(ray.light_n):
    				intersect = False
    				point = e + mint * D
    				for k in range(ob.surface_n):
    					if((ob.surface[k]['type'] == 'Sphere') and (k != minob_n)):
    						shadow_D = ray.light[r]['position'] - point
    						shadow_T = ob.sphere(k, point, shadow_D)
    						if(shadow_T != math.inf):
    							shadow_rt = point + shadow_T * shadow_D
    							if(np.dot(shadow_rt - point, shadow_D) > 0):
    								color = color + np.array([0,0,0])
    								intersect = True
    					elif((ob.surface[k]['type'] == 'Box') and (k != minob_n)):
    						point = e + mint * vector_normalize(D)
    						shadow_D = vector_normalize(ray.light[r]['position'] - point)
    						shadow_T = ob.box(k, point, shadow_D)
    						if(shadow_T != math.inf):
    							shadow_rt = point + shadow_T * shadow_D
    							if(np.dot(shadow_rt - point, shadow_D) > 0):
    								color = color + np.array([0,0,0]) 
    								intersect = True
    				if(intersect == False):
    					color = color + ob.shading(mint, ray, i, j, minob_n, r, S, img, e)

    				


    			c = Color(color[0],color[1],color[2])
    			c.gammaCorrect(2.2)
    			img[j][i] = c.toUINT8()

    rawimg = Image.fromarray(img, 'RGB')
    #rawimg.save('out.png')
    rawimg.save(sys.argv[1]+'.png')
    
if __name__=="__main__":
    main()
