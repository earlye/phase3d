== Overview ==

This is my attempt at producing a high-quality, scalable, extensible
ray tracer.

I intend to implement a number of capabilities:

* Extensible scene format, including the ability to use a distributed
  database for the scene graph. The goal here is to support billions
  of objects in a scene, in a reasonable timeframe.

* Extensible output format, including the ability to use a distributed
  database for the output buffers. The goal here is to support
  rendering ridiculously large images. 4k is child's play, as far as I'm
  concerned: I want to render billboards at 600+ dpi.

* Proper 3d primitives with constructive solid geometry, as opposed to
  tesselation (though triangle and quad meshes are obviously going to
  be supported, too)

* Volumetric effects like fog.

* Photon mapping

* Global Illumination, diffuse interreflection

* NURBS

* Instancing

* Motion Blur



