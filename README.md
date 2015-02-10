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

* Selectable precision

== Architecture ==

I'm choosing C++11 as the implementation language for a few reasons:

* I like it.

* Its templating gives me selectable precision without a huge chunk of
  effort and zero runtime cost - provided I'm happy with compile-time
  precision selection. Luckily, I'm very happy with that.

* I can use this project to help test my other project, Fabricator

* The process will eventually be split into a few phases. Each phase
  could conceivably be implemented as multiple threads on different
  servers, though it seems that each phase must complete in its
  entirety prior to the next phase running.

** importer - reads scene graph from source file(s) into the database
   for a particular timestamp or range of timestamps. The database
   will maintain a set of start/end timestamps for each object.

** bvh-generator - reads objects from the database at specific
   timestamps to determine their bounding volumes, and builds a
   bounding volume heirarchy accordingly.

** photon-mapper - traces photons from light sources through the scene
   in order to produce effects like cuastics

** tile-tracer - casts rays from the camera(s) into the scene at a
   given timestamp, using the BVH to keep render times
   reasonable. Depending on GI and quality settings, can generate many
   incident rays at each intersection.

** down-sampler - averages the results of multiple timestamps and
   subpixels to produce rendered frames.

* A manager of some sort will be responsible for coordinating the
  efforts of the various phases. It is conceivable, if not expected,
  that certain of these phases will be significantly faster/slower
  than the others. For example, the importer phase is likely to be
  significantly faster than the tile-tracer. However, we don't
  necessarily want it to get thousands of frames ahead of the
  tile-tracer, because that could easily cause the database system to
  run out of space.

* The manager will therefore have to provide some sort of semaphore
  mechanism, so that as the importer determines it's ready for the
  bvh-generator to run for a timestamp, the bvh-generators gen be let
  loose, and as they realize a particular timestamp is good for
  photon-mapping, they can let photon-mappers loose, and so on.

* The fact that geometry will be stored on the database implies that
  the tile tracer can conceivably be split into two: ray generation
  and ray coallescence. Basically, ray generation just puts into a
  queue a set of rays for a given time stamp, while a ray coallescer
  checks the results of ray calculations from multiple nodes to see
  which is the "closest" to the ray's origin.  It may be interesting
  if bounding volumes retain information about which node(s) contain
  the list of bounded objects. The tracers could then be implemented
  such that each node can quickly determine if an entire node can be
  skipped when doing intersection tests.


