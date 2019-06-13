// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#include "ParticleParams.h"

// Search/replace pattern to convert struct member declarations to VAR_INFO declarations
//{:b*}{.*}:b+{[a-z0-9_]+};:b*// {.*}
//\1VAR_INFO_ATTRS(\3, "\4")

// Version for comment-only lines
// {.*}
//ATTRS_INFO("\1")

// *INDENT-OFF* - disable uncrustify's indenting, as it doesn't make sense here.

STRUCT_INFO_BEGIN(RandomColor)
	BASE_INFO(UnitFloat8)
	VAR_INFO(m_bRandomHue)
STRUCT_INFO_END(RandomColor)

STRUCT_INFO_T_BEGIN(TVarParam, class, S)
	BASE_INFO(S)
	VAR_INFO_ATTRS(m_Random, "Random variation, fraction range = [1-Random,1].")
STRUCT_INFO_T_END(TVarParam, class, S)

STRUCT_INFO_T_BEGIN(TVarEParam, class, S)
	BASE_INFO(TVarParam<S>)
	VAR_INFO_ATTRS(m_EmitterStrength, "Value variance with emitter Strength, or emitter age if Strength < 0")
STRUCT_INFO_T_END(TVarEParam, class, S)

STRUCT_INFO_T_BEGIN(TVarEPParam, class, S)
	BASE_INFO(TVarEParam<S>)
	VAR_INFO_ATTRS(m_ParticleAge, "Value variance with particle age")
STRUCT_INFO_T_END(TVarEPParam, class, S)

STRUCT_INFO_T_BEGIN(TRangeParam, class, S)
	VAR_INFO(Min)
	VAR_INFO(Max)
STRUCT_INFO_T_END(TRangeParam, class, S)

STRUCT_INFO_BEGIN(ParticleParams::STextureTiling)
	VAR_INFO_ATTRS(nTilesX, "Number of columns texture is split into")
	VAR_INFO_ATTRS(nTilesY, "Number of rows texture is split into")
	VAR_INFO_ATTRS(nFirstTile, "First (or only) tile to use")
	VAR_INFO_ATTRS(nVariantCount, "Number of randomly selectable tiles; 0 or 1 if no variation")
	VAR_INFO_ATTRS(nAnimFramesCount, "Number of tiles (frames) of animation; 0 or 1 if no animation")
	VAR_INFO_ATTRS(fAnimFramerate, "<SoftMax=60> Tex framerate; 0 = 1 cycle / particle life")
	VAR_INFO_ATTRS(eAnimCycle, "How animation cycles")
	VAR_INFO_ATTRS(bAnimBlend, "Blend textures between frames")
	VAR_INFO_ATTRS(fFlipChance, "Chance each particle will flip in X direction")
	VAR_INFO_ATTRS(fAnimCurve, "Animation curve")
STRUCT_INFO_END(ParticleParams::STextureTiling)

ENUM_INFO_BEGIN(EGeomType)
	ENUM_ELEM_INFO(, GeomType_None)
	ENUM_ELEM_INFO(, GeomType_BoundingBox)
	ENUM_ELEM_INFO(, GeomType_Physics)
	ENUM_ELEM_INFO(, GeomType_Render)
ENUM_INFO_END(EGeomType)

ENUM_INFO_BEGIN(EGeomForm)
	ENUM_ELEM_INFO(, GeomForm_Vertices)
	ENUM_ELEM_INFO(, GeomForm_Edges)
	ENUM_ELEM_INFO(, GeomForm_Surface)
	ENUM_ELEM_INFO(, GeomForm_Volume)
ENUM_INFO_END(EGeomForm)

ENUM_INFO_BEGIN(CryAudio::EOcclusionType)
	ENUM_ELEM_INFO(CryAudio::, EOcclusionType::Ignore)
	ENUM_ELEM_INFO(CryAudio::, EOcclusionType::Adaptive)
	ENUM_ELEM_INFO(CryAudio::, EOcclusionType::Low)
	ENUM_ELEM_INFO(CryAudio::, EOcclusionType::Medium)
	ENUM_ELEM_INFO(CryAudio::, EOcclusionType::High)
ENUM_INFO_END(CryAudio::EOcclusionType)

STRUCT_INFO_BEGIN(ParticleParams)
	ATTRS_INFO("<Group=Emitter>")
	VAR_INFO(sComment)
	VAR_INFO_ATTRS(bEnabled, "Set false to disable this effect")
	VAR_INFO_ATTRS(eInheritance, "Source of ParticleParams used as base for this effect (for serialization, display, etc)")
	VAR_INFO_ATTRS(eSpawnIndirection, "Direct: spawn from emitter location; else spawn from each particle in parent emitter")
	VAR_INFO_ATTRS(fCount, "Number of particles alive at once")
	VAR_INFO_ATTRS(fMaintainDensity, "<SoftMax=1> Increase count when emitter moves to maintain spatial density")

	ATTRS_INFO("<Group=Timing>")
	VAR_INFO_ATTRS(bContinuous, "Emit particles gradually until Count reached (rate = Count / ParticleLifeTime)")
	VAR_INFO_ATTRS(fSpawnDelay, "Delay the emitter start time by this value	")
	VAR_INFO_ATTRS(fEmitterLifeTime, "Lifetime of the emitter, 0 if infinite. Always emits at least Count particles")
	VAR_INFO_ATTRS(fPulsePeriod, "Time between auto-restarts of emitter; 0 if never")
	VAR_INFO_ATTRS(fParticleLifeTime, "Lifetime of particles, 0 if indefinite (die with emitter)")
	VAR_INFO_ATTRS(bRemainWhileVisible, "Particles will only die when not rendered (by any viewport)")

	ATTRS_INFO("<Group=Location>")
	VAR_INFO_ATTRS(vPositionOffset, "Spawn offset from the emitter position")
	VAR_INFO_ATTRS(vRandomOffset, "Random offset of emission relative position to the spawn position")
	VAR_INFO_ATTRS(fOffsetRoundness, "Fraction of emit volume corners to round: 0 = box, 1 = ellipsoid")
	VAR_INFO_ATTRS(fOffsetInnerFraction, "Fraction of inner emit volume to avoid")
	VAR_INFO_ATTRS(eAttachType, "Which geometry to use for attached entity")
	VAR_INFO_ATTRS(eAttachForm, "Which aspect of attached geometry to emit from")

	ATTRS_INFO("<Group=Angles>")
	VAR_INFO_ATTRS(fFocusAngle, "Angle to vary focus from default (Y axis), for variation")
	VAR_INFO_ATTRS(fFocusAzimuth, "<SoftMax=360> Angle to rotate focus about default, for variation. 0 = Z axis")
	VAR_INFO_ATTRS(fFocusCameraDir, "Rotate emitter focus partially or fully to face camera")
	VAR_INFO_ATTRS(bFocusGravityDir, "Uses negative gravity dir, rather than emitter Y, as focus dir")
	VAR_INFO_ATTRS(bFocusRotatesEmitter, "Focus rotation is equivalent to emitter rotation; else affects just emission direction")
	VAR_INFO_ATTRS(bEmitOffsetDir, "Default emission direction parallel to emission offset from origin")
	VAR_INFO_ATTRS(fEmitAngle, "Angle from focus dir (emitter Y), in degrees. RandomVar determines min angle")
	VAR_INFO_ATTRS(eFacing, "Orientation of particle face")
	VAR_INFO_ATTRS(bOrientToVelocity, "Particle X axis aligned to velocity direction")
	VAR_INFO_ATTRS(fCurvature, "For Facing=Camera, fraction that normals are curved to a spherical shape")

	ATTRS_INFO("<Group=Appearance>")
	VAR_INFO_ATTRS(eBlendType, "Blend rendering type")
	VAR_INFO_ATTRS(sTexture, "Texture asset for sprite")
	VAR_INFO_ATTRS(TextureTiling, "Tiling of texture for animation and variation")
	VAR_INFO_ATTRS(sMaterial, "Material (overrides texture)")
	VAR_INFO_ATTRS(bTessellation, "If hardware supports, tessellate particles for better shadowing and curved connected particles")
	VAR_INFO_ATTRS(bOctagonalShape, "Use octagonal shape for textures instead of quad")
	VAR_INFO_ATTRS(bSoftParticle, "Soft intersection with background")
	VAR_INFO_ATTRS(sGeometry, "Geometry for 3D particles")
	VAR_INFO_ATTRS(eGeometryPieces, "Which geometry pieces to emit")
	VAR_INFO_ATTRS(bNoOffset, "Disable centering of geometry")
	VAR_INFO_ATTRS(fAlpha, "<SoftMax=1> Alpha value (opacity, or multiplier for additive)")
	VAR_INFO_ATTRS(AlphaClip, "Alpha clipping settings, for particle alpha 0 to 1")
	VAR_INFO_ATTRS(cColor, "Color modulation")

	ATTRS_INFO("<Group=Lighting>")
	VAR_INFO_ATTRS(fDiffuseLighting, "<SoftMax=1> Multiplier for particle dynamic lighting")
	VAR_INFO_ATTRS(fDiffuseBacklighting, "Fraction of diffuse lighting applied in all directions")
	VAR_INFO_ATTRS(fEmissiveLighting, "<SoftMax=1> Multiplier for particle emissive lighting")
	VAR_INFO_ATTRS(bReceiveShadows, "Shadows will cast on these particles")
	VAR_INFO_ATTRS(bCastShadows, "Particles will cast shadows (currently only geom particles)")
	VAR_INFO_ATTRS(bNotAffectedByFog, "Ignore fog")
	VAR_INFO_ATTRS(LightSource, "Per-particle light generation")

	ATTRS_INFO("<Group=Audio>")
	VAR_INFO_ATTRS(sStartTrigger, "Audio start-trigger to execute")
	VAR_INFO_ATTRS(sStopTrigger, "Audio stop-trigger to execute")
	VAR_INFO_ATTRS(fSoundFXParam, "Custom real-time sound modulation parameter")
	VAR_INFO_ATTRS(eSoundControlTime, "The sound control time type")

	ATTRS_INFO("<Group=Size>")
	VAR_INFO_ATTRS(fSize, "<SoftMax=8> Particle radius, for sprites; size scale for geometry")
	VAR_INFO_ATTRS(fAspect, "<SoftMax=8> X-to-Y scaling factor")
	VAR_INFO_ATTRS(fPivotX, "<SoftMin=-1> <SoftMax=1> Pivot offset in X direction")
	VAR_INFO_ATTRS(fPivotY, "<SoftMin=-1> <SoftMax=1> Pivot offset in Y direction")

	VAR_INFO_ATTRS(fStretch, "<SoftMax=1> Stretch particle into moving direction, amount in seconds")
	VAR_INFO_ATTRS(fTailLength, "<SoftMax=10> Length of tail in seconds")
	VAR_INFO_ATTRS(fMinPixels, "<SoftMax=10> Augment true size with this many pixels")

	VAR_INFO_ATTRS(Connection, "Particles are drawn connected serially")

	ATTRS_INFO("<Group=Movement>")
	VAR_INFO_ATTRS(fSpeed, "Initial speed of a particle")
	VAR_INFO_ATTRS(fInheritVelocity, "<SoftMin=0> $<SoftMax=1> Fraction of emitter's velocity to inherit")
	VAR_INFO_ATTRS(fAirResistance, "<SoftMax=10> Air drag value, in inverse seconds")
	VAR_INFO_ATTRS(fGravityScale, "<SoftMin=-1> $<SoftMax=1> Multiplier for world gravity")
	VAR_INFO_ATTRS(vAcceleration, "Explicit world-space acceleration vector")
	VAR_INFO_ATTRS(fTurbulence3DSpeed, "<SoftMax=10> 3D random turbulence force")
	VAR_INFO_ATTRS(fTurbulenceSize, "<SoftMax=10> Radius of vortex rotation (axis is direction of movement)")
	VAR_INFO_ATTRS(fTurbulenceSpeed, "<SoftMin=-360> $<SoftMax=360> Angular speed of vortex rotation")

	VAR_INFO_ATTRS(bMoveRelativeEmitter, "Particle motion is in emitter space")
	VAR_INFO_ATTRS(bBindEmitterToCamera, "Emitter is camera-relative")
	VAR_INFO_ATTRS(bSpaceLoop, "Loops particles within emission volume, or within Camera Max Distance")
	VAR_INFO(TargetAttraction)

	ATTRS_INFO("<Group=Rotation>")
	VAR_INFO_ATTRS(vInitAngles, "Initial rotation in symmetric angles (degrees)")
	VAR_INFO_ATTRS(vRandomAngles, "Bidirectional random angle variation")
	VAR_INFO_ATTRS(vRotationRate, "<SoftMin=-360> $<SoftMax=360> Rotation speed (degree/sec)")
	VAR_INFO_ATTRS(vRandomRotationRate, "<SoftMax=360> Random variation of rotation speed")

	ATTRS_INFO("<Group=Collision>")
	VAR_INFO_ATTRS(ePhysicsType, "What kind of physics simulation to run on particle")
	VAR_INFO_ATTRS(bCollideTerrain, "Collides with terrain (if Physics <> none)")
	VAR_INFO_ATTRS(bCollideStaticObjects, "Collides with static physics objects (if Physics <> none)")
	VAR_INFO_ATTRS(bCollideDynamicObjects, "Collides with dynamic physics objects (if Physics <> none)")
	VAR_INFO_ATTRS(fCollisionFraction, "Fraction of emitted particles that actually perform collisions")
	VAR_INFO_ATTRS(fCollisionCutoffDistance, "Maximum distance up until collisions are respected (0 = infinite)")
	VAR_INFO_ATTRS(nMaxCollisionEvents, "Max # collision events per particle (0 = no limit)")
	VAR_INFO_ATTRS(eFinalCollision, "What to do on final collision (when MaxCollisions > 0")
	VAR_INFO_ATTRS(sSurfaceType, "Surface type for physicalized particles")
	VAR_INFO_ATTRS(fElasticity, "$<SoftMax=1> Collision bounce coefficient: 0 = no bounce, 1 = full bounce, <0 = die")
	VAR_INFO_ATTRS(fDynamicFriction, "<SoftMax=10> Sliding drag value, in inverse seconds")
	VAR_INFO_ATTRS(fThickness, "<SoftMax=1> Lying thickness ratio - for physicalized particles only")
	VAR_INFO_ATTRS(fDensity, "<SoftMax=2000> Mass density for physicslized particles")

	ATTRS_INFO("<Group=Visibility>")
	VAR_INFO_ATTRS(fViewDistanceAdjust, "<SoftMax=1> Multiplier to automatic distance fade-out")
	VAR_INFO_ATTRS(fCameraMaxDistance, "<SoftMax=100> Max distance from camera to render particles")
	VAR_INFO_ATTRS(fCameraMinDistance, "<SoftMax=100> Min distance from camera to render particles")
	VAR_INFO_ATTRS(fCameraDistanceOffset, "<SoftMin=-1> <SoftMax=1> Offset the emitter away from the camera")
	VAR_INFO_ATTRS(fSortOffset, "<SoftMin=-1> <SoftMax=1> Offset distance used for sorting")
	VAR_INFO_ATTRS(fSortBoundsScale, "<SoftMin=-1> <SoftMax=1> Specify point in emitter for sorting; 1 = bounds nearest, 0 = origin, -1 = bounds farthest")
	VAR_INFO_ATTRS(bDrawNear, "Render particle in near space (weapon)")
	VAR_INFO_ATTRS(bDrawOnTop, "Render particle on top of everything (no depth test)")
	VAR_INFO_ATTRS(tVisibleIndoors, "Whether visible indoors / outdoors / both")
	VAR_INFO_ATTRS(tVisibleUnderwater, "Whether visible under / above water / both")
	VAR_INFO_ATTRS(fFadeAtViewCosAngle, "Fades particles out besed on their angle to the camera")

	ATTRS_INFO("<Group=Advanced>")
	VAR_INFO_ATTRS(eForceGeneration, "Generate physical forces if set")
	VAR_INFO_ATTRS(fFillRateCost, "Adjustment to max screen fill allowed per emitter")
	VAR_INFO_ATTRS(fHeatScale, "Multiplier to thermal vision")
	VAR_INFO_ATTRS(fSphericalApproximation, "align the particle to the tangent of the sphere")
	VAR_INFO_ATTRS(fPlaneAlignBlendDistance, "<SoftMin=0><SoftMax=100> Distance when blend to camera plane aligned particles starts")

	VAR_INFO_ATTRS(nSortQuality, "Sort new particles as accurately as possible into list, by main camera distance")
	VAR_INFO_ATTRS(bForceDynamicBounds, "Always update particles and compute actual bounds for visibility")
	VAR_INFO_ATTRS(bHalfRes, "Use half resolution rendering")
	VAR_INFO_ATTRS(bStreamable, "Texture/geometry allowed to be streamed")
	VAR_INFO_ATTRS(bVolumeFog, "Use as a participating media of volumetric fog")
	VAR_INFO_ATTRS(fVolumeThickness, "Thickness of participating media, scale for particle size")

	ATTRS_INFO("<Group=Configuration>")
	VAR_INFO_ATTRS(eConfigMin, "Minimum config spec this effect runs in")
	VAR_INFO_ATTRS(eConfigMax, "Maximum config spec this effect runs in")
	VAR_INFO_ATTRS(Platforms, "Platforms this effect runs on")
STRUCT_INFO_END(ParticleParams)

STRUCT_INFO_BEGIN(ParticleParams::SMaintainDensity)
	BASE_INFO(UFloat)
	VAR_INFO_ATTRS(fReduceLifeTime, "<SoftMax=1> Reduce life time inversely to count increase")
	VAR_INFO_ATTRS(fReduceAlpha, "<SoftMax=1> Reduce alpha inversely to count increase")
	VAR_INFO_ATTRS(fReduceSize, "<SoftMax=1> Reduce size inversely to count increase")
STRUCT_INFO_END(ParticleParams::SMaintainDensity)

STRUCT_INFO_BEGIN(ParticleParams::SSoftParticle)
	BASE_INFO(TSmallBool)
	VAR_INFO_ATTRS(fSoftness, "<SoftMax=2> Soft particle scale")
STRUCT_INFO_END(ParticleParams::SSoftParticle)

STRUCT_INFO_BEGIN(ParticleParams::SAirResistance)
	BASE_INFO(TVarEPParam<UFloat>)
	VAR_INFO_ATTRS(fRotationalDragScale, "<SoftMax=1> Multiplier to AirResistance, for rotational motion")
	VAR_INFO_ATTRS(fWindScale, "<SoftMax=1> Artificial adjustment to environmental wind")
STRUCT_INFO_END(ParticleParams::SAirResistance)

STRUCT_INFO_BEGIN(ParticleParams::SAlphaClip)
	VAR_INFO_ATTRS(fScale, "<SoftMax=1> Alpha multiplier for particle alpha 0 to 1")
	VAR_INFO_ATTRS(fSourceMin, "Source alpha clip min, for particle alpha 0 to 1")
	VAR_INFO_ATTRS(fSourceWidth, "Source alpha clip range, for particle alpha 0 to 1")
STRUCT_INFO_END(ParticleParams::SAlphaClip)

STRUCT_INFO_BEGIN(ParticleParams::SLightSource)
	VAR_INFO_ATTRS(bAffectsThisAreaOnly, "Light source affects current clip volume only")
	VAR_INFO_ATTRS(fRadius, "<SoftMax=10> Radius of light")
	VAR_INFO_ATTRS(fIntensity, "<SoftMax=10> Intensity of light (color from Appearance/Color)")
	VAR_INFO_ATTRS(eLightAffectsFog, "Light source affects volumetric fog")
STRUCT_INFO_END(ParticleParams::SLightSource)

STRUCT_INFO_BEGIN(ParticleParams::SConnection)
	BASE_INFO(TSmallBool)
	VAR_INFO_ATTRS(bConnectToOrigin, "Newest particle connected to emitter origin")
	VAR_INFO_ATTRS(eTextureMapping, "Basis of texture coord mapping (particle or stream)")
	VAR_INFO_ATTRS(bTextureMirror, "Mirror alternating texture tiles; else wrap")
	VAR_INFO_ATTRS(fTextureFrequency, "<SoftMax=8> Number of texture wraps per particle or sequence")
STRUCT_INFO_END(ParticleParams::SConnection)

STRUCT_INFO_BEGIN(ParticleParams::STargetAttraction)
	VAR_INFO_ATTRS(eTarget, "Source of target attractor")
	VAR_INFO_ATTRS(bExtendSpeed, "Extend particle speed as necessary to reach target in normal lifetime")
	VAR_INFO_ATTRS(bShrink, "Shrink particle as it approaches target")
	VAR_INFO_ATTRS(bOrbit, "Orbit target at specified distance, rather than disappearing")
	VAR_INFO_ATTRS(fRadius, "Distance from attractor for vanishing or orbiting")
STRUCT_INFO_END(ParticleParams::STargetAttraction)

STRUCT_INFO_BEGIN(ParticleParams::SStretch)
	BASE_INFO_ATTRS(TVarEPParam<UFloat>, "<SoftMax=1>")
	VAR_INFO_ATTRS(fOffsetRatio, "<SoftMin=-1> $<SoftMax=1> Move particle center this fraction in direction of stretch")
STRUCT_INFO_END(ParticleParams::SStretch)

STRUCT_INFO_BEGIN(ParticleParams::STailLength)
	BASE_INFO_ATTRS(TVarEPParam<UFloat>, "<SoftMax=10>")
	VAR_INFO_ATTRS(nTailSteps, "<SoftMax=16> Number of tail segments")
STRUCT_INFO_END(ParticleParams::STailLength)

STRUCT_INFO_BEGIN(ParticleParams::SMoveRelativeEmitter)
	BASE_INFO(TSmallBool)
	VAR_INFO_ATTRS(bIgnoreRotation, "Ignore emitter rotation when updating particles")
	VAR_INFO_ATTRS(bIgnoreSize, "Ignore emitter size when updating particles")
	VAR_INFO_ATTRS(bMoveTail, "Tail segments also move with emitter")
STRUCT_INFO_END(ParticleParams::SMoveRelativeEmitter)

STRUCT_INFO_BEGIN(ParticleParams::SPlatforms)
	VAR_INFO(PCDX)
	VAR_INFO(PS4)
	VAR_INFO(XBoxOne)
	VAR_INFO(XBoxOneX)
STRUCT_INFO_END(ParticleParams::SPlatforms)

// *INDENT-ON* - disable uncrustify's indenting, as it doesn't make sense here.
