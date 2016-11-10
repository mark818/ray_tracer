README:

Partners:
Yichao Shen & Chuhan Zhang
adj & abf

Working environmnt:
Mac OS

Location of Source Code:
at abf in as2 directory


References:
1. RayTriangle Intersection referference source:
http://www.scratchapixel.com/lessons/3d-basic-rendering

NOTE:
• All the renders and timings are done on Windows 10 with i7-4710 CPU 12G DDR3 RAM.
But the final script conforms to the running in Mac OS, so the timing might be different.
• If recompile, pease "make clean" then "make".

EXTRA CREDIT：
• accelerating ray tests -- AABB & BVH

argument line:
leaf n

n: size of max_leaf in each AABB for the model

This feature is shown in notes-01 by comparing the running time of 
leaf 4 (each minimum AABB contains 4 primitives)
and  
leaf 100000 (all primitives are in one AABB, same as the case of 
not using BVH)

• Area light

argument line:
ltar llx lly llz lrx lry lrz ulx uly ulz urx ury urz r g b size

size: number of final modeled point lights from this area defined
by ll, lr, ul, ur.

This feature is shown in notes-07 by using a area light to generate 
umbra and penumbra.

• Anti-aliasing

argument line:
aa n

n: perfect square for number of samples per pixel

This feature is shown in notes-02 where the image is clearer and has 
fade color at the edge compared to image-01 with arguments (aa 1:aa 64)

• depth of field

argument line:
dof z aperture

z: the z coordinate of focus
aperture: aperture meaning in camera

This feature is shown in notes-08 where the front part is clear and the back parts not in focus.

• Other interesting features -- Multiple threads running for speed 

argument line:
t n 

n: number of threads concurrently runnning

This feature is shown in notes-01 where the running time of (t 1:t 8)
differs obviously. The one with t:8 use lesser time.
