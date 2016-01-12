%{
#define SWIG_FILE_WITH_INIT // In case we use Python Swig Wrapping

#include "resqml2_0_1/LocalDepth3dCrs.h"
#include "resqml2_0_1/LocalTime3dCrs.h"
#include "resqml2_0_1/MdDatum.h"

#include "resqml2_0_1/Horizon.h"
#include "resqml2_0_1/Fault.h"
#include "resqml2_0_1/Fracture.h"
#include "resqml2_0_1/FrontierFeature.h"
#include "resqml2_0_1/WellboreFeature.h"
#include "resqml2_0_1/SeismicLineFeature.h"
#include "resqml2_0_1/SeismicLineSetFeature.h"
#include "resqml2_0_1/SeismicLatticeFeature.h"
#include "resqml2_0_1/OrganizationFeature.h"
#include "resqml2_0_1/StratigraphicUnitFeature.h"
#include "resqml2_0_1/FluidBoundaryFeature.h"

#include "resqml2_0_1/GenericFeatureInterpretation.h"
#include "resqml2_0_1/HorizonInterpretation.h"
#include "resqml2_0_1/FaultInterpretation.h"
#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/StratigraphicUnitInterpretation.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"
#include "resqml2_0_1/StratigraphicColumnRankInterpretation.h"
#include "resqml2_0_1/StratigraphicOccurrenceInterpretation.h"
#include "resqml2_0_1/EarthModelInterpretation.h"

#include "resqml2_0_1/PolylineSetRepresentation.h"
#include "resqml2_0_1/PointSetRepresentation.h"
#include "resqml2_0_1/PlaneSetRepresentation.h"
#include "resqml2_0_1/PolylineRepresentation.h"
#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2_0_1/Grid2dSetRepresentation.h"
#include "resqml2_0_1/TriangulatedSetRepresentation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2_0_1/WellboreMarker.h"
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"
#include "resqml2_0_1/NonSealedSurfaceFrameworkRepresentation.h"
#include "resqml2_0_1/SealedSurfaceFrameworkRepresentation.h"

#include "resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "resqml2_0_1/IjkGridParametricRepresentation.h"
#include "resqml2_0_1/IjkGridLatticeRepresentation.h"
#include "resqml2_0_1/IjkGridNoGeometryRepresentation.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/SubRepresentation.h"
#include "resqml2_0_1/GridConnectionSetRepresentation.h"

#include "resqml2_0_1/TimeSeries.h"

#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/StringTableLookup.h"
#include "resqml2_0_1/DiscreteProperty.h"
#include "resqml2_0_1/DiscretePropertySeries.h"
#include "resqml2_0_1/CategoricalProperty.h"
#include "resqml2_0_1/CategoricalPropertySeries.h"
#include "resqml2_0_1/CommentProperty.h"
#include "resqml2_0_1/ContinuousProperty.h"
#include "resqml2_0_1/ContinuousPropertySeries.h"

#include "resqml2_0_1/ActivityTemplate.h"

#include "resqml2_0_1/HdfProxy.h"
#include "resqml2_0_1/PropertyKindMapper.h"
%}
typedef long long					LONG64;

#ifdef SWIGJAVA
typedef long long					ULONG64; // We don't want o use BigInteger in java.
#else
typedef unsigned long long	ULONG64;
#endif

typedef long long 				time_t;


//************************
// STD::VECTOR DEFINITIONS
//************************

namespace resqml2_0_1 {
	class Activity;
	class LocalDepth3dCrs;
	class LocalTime3dCrs;
	class StratigraphicColumn;
	class StratigraphicColumnRankInterpretation;
	class Fault;
	class Fracture;
	class Horizon;
	class FrontierFeature;
	class StratigraphicUnitInterpretation;
	class HorizonInterpretation;
	class StratigraphicOccurrenceInterpretation;
	class PolylineSetRepresentation;
	class Grid2dSetRepresentation;
	class Grid2dRepresentation;
	class PolylineRepresentation;
	class PolylineSetRepresentation;
	class TriangulatedSetRepresentation;
	class SeismicLineFeature;
	class WellboreFeature;
	class WellboreTrajectoryRepresentation;
	class WellboreMarkerFrameRepresentation;
	class UnstructuredGridRepresentation;
	class WellboreMarker;
	class IjkGridExplicitRepresentation;
	class IjkGridParametricRepresentation;
	class IjkGridLatticeRepresentation;
	class IjkGridNoGeometryRepresentation;
}

// Don't try to create vector of polymorphic data unless you really know what you are doing.
// Use C array approach instead.
%include "std_vector.i"
namespace std {
   %template(ActivityVector) vector<resqml2_0_1::Activity*>;
   %template(LocalDepth3dCrsVector) vector<resqml2_0_1::LocalDepth3dCrs*>;
   %template(LocalTime3dCrsVector) vector<resqml2_0_1::LocalTime3dCrs*>;
   %template(StratigraphicColumnVector) vector<resqml2_0_1::StratigraphicColumn*>;
   %template(StratigraphicColumnRankInterpretationVector) vector<resqml2_0_1::StratigraphicColumnRankInterpretation*>;
   %template(FaultVector) vector<resqml2_0_1::Fault*>;
   %template(FractureVector) vector<resqml2_0_1::Fracture*>;
   %template(HorizonVector) vector<resqml2_0_1::Horizon*>;
   %template(FrontierVector) vector<resqml2_0_1::FrontierFeature*>;
   %template(StratigraphicUnitInterpretationVector) vector<resqml2_0_1::StratigraphicUnitInterpretation*>;
   %template(StratigraphicOccurrenceInterpretationVector) vector<resqml2_0_1::StratigraphicOccurrenceInterpretation*>;
   %template(HorizonInterpretationVector) vector<resqml2_0_1::HorizonInterpretation*>;
   %template(Grid2dSetRepresentationVector) vector<resqml2_0_1::Grid2dSetRepresentation*>;
   %template(Grid2dRepresentationVector) vector<resqml2_0_1::Grid2dRepresentation*>;
   %template(PolylineRepresentationVector) vector<resqml2_0_1::PolylineRepresentation*>;
   %template(PolylineSetRepresentationVector) vector<resqml2_0_1::PolylineSetRepresentation*>;
   %template(TriangulatedSetRepresentationVector) vector<resqml2_0_1::TriangulatedSetRepresentation*>;
   %template(SeismicLineFeatureVector) vector<resqml2_0_1::SeismicLineFeature*>;
   %template(WellboreFeatureVector) vector<resqml2_0_1::WellboreFeature*>;
   %template(WellboreTrajectoryRepresentationVector) vector<resqml2_0_1::WellboreTrajectoryRepresentation*>;
   %template(WellboreMarkerFrameRepresentationVector) vector<resqml2_0_1::WellboreMarkerFrameRepresentation*>;
   %template(UnstructuredGridRepresentationVector) vector<resqml2_0_1::UnstructuredGridRepresentation*>;
   %template(StringVector) vector<std::string>;
   %template(WellboreMarkerVector) vector<resqml2_0_1::WellboreMarker*>;
   %template(IjkGridExplicitRepresentationVector) vector<resqml2_0_1::IjkGridExplicitRepresentation*>;
   %template(IjkGridParametricRepresentationVector) vector<resqml2_0_1::IjkGridParametricRepresentation*>;
   %template(IjkGridLatticeRepresentationVector) vector<resqml2_0_1::IjkGridLatticeRepresentation*>;
   %template(IjkGridNoGeometryRepresentationVector) vector<resqml2_0_1::IjkGridNoGeometryRepresentation*>;
}

namespace gsoap_resqml2_0_1
{
	enum eml__AxisOrder2d { eml__AxisOrder2d__easting_x0020northing = 0, eml__AxisOrder2d__northing_x0020easting = 1, eml__AxisOrder2d__westing_x0020southing = 2, eml__AxisOrder2d__southing_x0020westing = 3, eml__AxisOrder2d__northing_x0020westing = 4, eml__AxisOrder2d__westing_x0020northing = 5 };
	enum resqml2__GeologicBoundaryKind { resqml2__GeologicBoundaryKind__fault = 0, resqml2__GeologicBoundaryKind__geobody = 1, resqml2__GeologicBoundaryKind__horizon = 2 };
	enum eml__LengthUom { eml__LengthUom__0_x002e1_x0020ft = 0, eml__LengthUom__0_x002e1_x0020ft_x005bUS_x005d = 1, eml__LengthUom__0_x002e1_x0020in = 2, eml__LengthUom__0_x002e1_x0020yd = 3, eml__LengthUom__1_x002f16_x0020in = 4, eml__LengthUom__1_x002f2_x0020ft = 5, eml__LengthUom__1_x002f32_x0020in = 6, eml__LengthUom__1_x002f64_x0020in = 7, eml__LengthUom__10_x0020ft = 8, eml__LengthUom__10_x0020in = 9, eml__LengthUom__10_x0020km = 10, eml__LengthUom__100_x0020ft = 11, eml__LengthUom__100_x0020km = 12, eml__LengthUom__1000_x0020ft = 13, eml__LengthUom__30_x0020ft = 14, eml__LengthUom__30_x0020m = 15, eml__LengthUom__angstrom = 16, eml__LengthUom__chain = 17, eml__LengthUom__chain_x005bBnA_x005d = 18, eml__LengthUom__chain_x005bBnB_x005d = 19, eml__LengthUom__chain_x005bCla_x005d = 20, eml__LengthUom__chain_x005bInd37_x005d = 21, eml__LengthUom__chain_x005bSe_x005d = 22, eml__LengthUom__chain_x005bSeT_x005d = 23, eml__LengthUom__chain_x005bUS_x005d = 24, eml__LengthUom__cm = 25, eml__LengthUom__dam = 26, eml__LengthUom__dm = 27, eml__LengthUom__Em = 28, eml__LengthUom__fathom = 29, eml__LengthUom__fm = 30, eml__LengthUom__ft = 31, eml__LengthUom__ft_x005bBnA_x005d = 32, eml__LengthUom__ft_x005bBnB_x005d = 33, eml__LengthUom__ft_x005bBr36_x005d = 34, eml__LengthUom__ft_x005bBr65_x005d = 35, eml__LengthUom__ft_x005bCla_x005d = 36, eml__LengthUom__ft_x005bGC_x005d = 37, eml__LengthUom__ft_x005bInd_x005d = 38, eml__LengthUom__ft_x005bInd37_x005d = 39, eml__LengthUom__ft_x005bInd62_x005d = 40, eml__LengthUom__ft_x005bInd75_x005d = 41, eml__LengthUom__ft_x005bSe_x005d = 42, eml__LengthUom__ft_x005bSeT_x005d = 43, eml__LengthUom__ft_x005bUS_x005d = 44, eml__LengthUom__fur_x005bUS_x005d = 45, eml__LengthUom__Gm = 46, eml__LengthUom__hm = 47, eml__LengthUom__in = 48, eml__LengthUom__in_x005bUS_x005d = 49, eml__LengthUom__km = 50, eml__LengthUom__link = 51, eml__LengthUom__link_x005bBnA_x005d = 52, eml__LengthUom__link_x005bBnB_x005d = 53, eml__LengthUom__link_x005bCla_x005d = 54, eml__LengthUom__link_x005bSe_x005d = 55, eml__LengthUom__link_x005bSeT_x005d = 56, eml__LengthUom__link_x005bUS_x005d = 57, eml__LengthUom__m = 58, eml__LengthUom__m_x005bGer_x005d = 59, eml__LengthUom__mi = 60, eml__LengthUom__mi_x005bnaut_x005d = 61, eml__LengthUom__mi_x005bnautUK_x005d = 62, eml__LengthUom__mi_x005bUS_x005d = 63, eml__LengthUom__mil = 64, eml__LengthUom__Mm = 65, eml__LengthUom__mm = 66, eml__LengthUom__nm = 67, eml__LengthUom__pm = 68, eml__LengthUom__rod_x005bUS_x005d = 69, eml__LengthUom__Tm = 70, eml__LengthUom__um = 71, eml__LengthUom__yd = 72, eml__LengthUom__yd_x005bBnA_x005d = 73, eml__LengthUom__yd_x005bBnB_x005d = 74, eml__LengthUom__yd_x005bCla_x005d = 75, eml__LengthUom__yd_x005bInd_x005d = 76, eml__LengthUom__yd_x005bInd37_x005d = 77, eml__LengthUom__yd_x005bInd62_x005d = 78, eml__LengthUom__yd_x005bInd75_x005d = 79, eml__LengthUom__yd_x005bSe_x005d = 80, eml__LengthUom__yd_x005bSeT_x005d = 81, eml__LengthUom__yd_x005bUS_x005d = 82 };

	enum eml__TimeUom { eml__TimeUom__1_x002f2_x0020ms = 0, eml__TimeUom__100_x0020ka_x005bt_x005d = 1, eml__TimeUom__a = 2, eml__TimeUom__a_x005bt_x005d = 3, eml__TimeUom__ca = 4, eml__TimeUom__cs = 5, eml__TimeUom__d = 6, eml__TimeUom__ds = 7, eml__TimeUom__Ea_x005bt_x005d = 8, eml__TimeUom__fa = 9, eml__TimeUom__Ga_x005bt_x005d = 10, eml__TimeUom__h = 11, eml__TimeUom__hs = 12, eml__TimeUom__ka_x005bt_x005d = 13, eml__TimeUom__Ma_x005bt_x005d = 14, eml__TimeUom__min_ = 15, eml__TimeUom__ms = 16, eml__TimeUom__na = 17, eml__TimeUom__ns = 18, eml__TimeUom__ps = 19, eml__TimeUom__s = 20, eml__TimeUom__Ta_x005bt_x005d = 21, eml__TimeUom__us = 22, eml__TimeUom__wk = 23 };
	enum resqml2__LineRole { resqml2__LineRole__fault_x0020center_x0020line = 0, resqml2__LineRole__pick = 1, resqml2__LineRole__inner_x0020ring = 2, resqml2__LineRole__outer_x0020ring = 3, resqml2__LineRole__trajectory = 4, resqml2__LineRole__interpretation_x0020line = 5, resqml2__LineRole__contact = 6, resqml2__LineRole__depositional_x0020line = 7, resqml2__LineRole__erosion_x0020line = 8, resqml2__LineRole__contouring = 9, resqml2__LineRole__pillar = 10 };
	enum resqml2__ContactVerb { resqml2__ContactVerb__splits = 0, resqml2__ContactVerb__interrupts = 1, resqml2__ContactVerb__contains = 2, resqml2__ContactVerb__conforms = 3, resqml2__ContactVerb__erodes = 4, resqml2__ContactVerb__stops_x0020at = 5, resqml2__ContactVerb__crosses = 6, resqml2__ContactVerb__includes = 7 };
	enum resqml2__ContactSide { resqml2__ContactSide__footwall = 0, resqml2__ContactSide__hanging_x0020wall = 1, resqml2__ContactSide__north = 2, resqml2__ContactSide__south = 3, resqml2__ContactSide__east = 4, resqml2__ContactSide__west = 5, resqml2__ContactSide__younger = 6, resqml2__ContactSide__older = 7, resqml2__ContactSide__both = 8 };
	enum resqml2__ContactMode { resqml2__ContactMode__baselap = 0, resqml2__ContactMode__erosion = 1, resqml2__ContactMode__extended = 2, resqml2__ContactMode__proportional = 3 };
	enum resqml2__ContactRelationship { resqml2__ContactRelationship__frontier_x0020feature_x0020to_x0020frontier_x0020feature = 0, resqml2__ContactRelationship__genetic_x0020boundary_x0020to_x0020frontier_x0020feature = 1, resqml2__ContactRelationship__genetic_x0020boundary_x0020to_x0020genetic_x0020boundary = 2, resqml2__ContactRelationship__genetic_x0020boundary_x0020to_x0020tectonic_x0020boundary = 3, resqml2__ContactRelationship__stratigraphic_x0020unit_x0020to_x0020frontier_x0020feature = 4, resqml2__ContactRelationship__stratigraphic_x0020unit_x0020to_x0020stratigraphic_x0020unit = 5, resqml2__ContactRelationship__tectonic_x0020boundary_x0020to_x0020frontier_x0020feature = 6, resqml2__ContactRelationship__tectonic_x0020boundary_x0020to_x0020genetic_x0020boundary = 7, resqml2__ContactRelationship__tectonic_x0020boundary_x0020to_x0020tectonic_x0020boundary = 8 };
	enum resqml2__ThrowKind { resqml2__ThrowKind__reverse = 0, resqml2__ThrowKind__normal = 1, resqml2__ThrowKind__thrust = 2, resqml2__ThrowKind__strike_x0020and_x0020slip = 3, resqml2__ThrowKind__scissor = 4, resqml2__ThrowKind__variable = 5 };
	enum resqml2__PillarShape { resqml2__PillarShape__vertical = 0, resqml2__PillarShape__straight = 1, resqml2__PillarShape__curved = 2 };
	enum resqml2__KDirection { resqml2__KDirection__down = 0, resqml2__KDirection__up = 1, resqml2__KDirection__not_x0020monotonic = 2 };
	enum resqml2__CellShape { resqml2__CellShape__tetrahedral = 0, resqml2__CellShape__pyramidal = 1, resqml2__CellShape__prism = 2, resqml2__CellShape__hexahedral = 3, resqml2__CellShape__polyhedral = 4 };
	enum resqml2__MdReference { resqml2__MdReference__ground_x0020level = 0, resqml2__MdReference__kelly_x0020bushing = 1, resqml2__MdReference__mean_x0020sea_x0020level = 2, resqml2__MdReference__derrick_x0020floor = 3, resqml2__MdReference__casing_x0020flange = 4, resqml2__MdReference__arbitrary_x0020point = 5, resqml2__MdReference__crown_x0020valve = 6, resqml2__MdReference__rotary_x0020bushing = 7, resqml2__MdReference__rotary_x0020table = 8, resqml2__MdReference__sea_x0020floor = 9, resqml2__MdReference__lowest_x0020astronomical_x0020tide = 10, resqml2__MdReference__mean_x0020higher_x0020high_x0020water = 11, resqml2__MdReference__mean_x0020high_x0020water = 12, resqml2__MdReference__mean_x0020lower_x0020low_x0020water = 13, resqml2__MdReference__mean_x0020low_x0020water = 14, resqml2__MdReference__mean_x0020tide_x0020level = 15, resqml2__MdReference__kickoff_x0020point = 16 };
	enum resqml2__IndexableElements { resqml2__IndexableElements__cells = 0, resqml2__IndexableElements__column_x0020edges = 1, resqml2__IndexableElements__columns = 2, resqml2__IndexableElements__contacts = 3, resqml2__IndexableElements__coordinate_x0020lines = 4, resqml2__IndexableElements__edges = 5, resqml2__IndexableElements__edges_x0020per_x0020column = 6, resqml2__IndexableElements__enumerated_x0020elements = 7, resqml2__IndexableElements__faces = 8, resqml2__IndexableElements__faces_x0020per_x0020cell = 9, resqml2__IndexableElements__interval_x0020edges = 10, resqml2__IndexableElements__intervals = 11, resqml2__IndexableElements__I0 = 12, resqml2__IndexableElements__I0_x0020edges = 13, resqml2__IndexableElements__J0 = 14, resqml2__IndexableElements__J0_x0020edges = 15, resqml2__IndexableElements__layers = 16, resqml2__IndexableElements__nodes = 17, resqml2__IndexableElements__nodes_x0020per_x0020cell = 18, resqml2__IndexableElements__nodes_x0020per_x0020edge = 19, resqml2__IndexableElements__nodes_x0020per_x0020face = 20, resqml2__IndexableElements__patches = 21, resqml2__IndexableElements__pillars = 22, resqml2__IndexableElements__regions = 23, resqml2__IndexableElements__representation = 24, resqml2__IndexableElements__subnodes = 25, resqml2__IndexableElements__triangles = 26 };
	enum resqml2__ResqmlUom { resqml2__ResqmlUom___x0025 = 0, resqml2__ResqmlUom___x0025_x005barea_x005d = 1, resqml2__ResqmlUom___x0025_x005bmass_x005d = 2, resqml2__ResqmlUom___x0025_x005bmolar_x005d = 3, resqml2__ResqmlUom___x0025_x005bvol_x005d = 4, resqml2__ResqmlUom___x0028bbl_x002fd_x0029_x002f_x0028bbl_x002fd_x0029 = 5, resqml2__ResqmlUom___x0028m3_x002fd_x0029_x002f_x0028m3_x002fd_x0029 = 6, resqml2__ResqmlUom___x0028m3_x002fs_x0029_x002f_x0028m3_x002fs_x0029 = 7, resqml2__ResqmlUom__0_x002e001_x0020bbl_x002fft3 = 8, resqml2__ResqmlUom__0_x002e001_x0020bbl_x002fm3 = 9, resqml2__ResqmlUom__0_x002e001_x0020d_x002fft3 = 10, resqml2__ResqmlUom__0_x002e001_x0020gal_x005bUK_x005d_x002fbbl = 11, resqml2__ResqmlUom__0_x002e001_x0020gal_x005bUK_x005d_x002fgal_x005bUK_x005d = 12, resqml2__ResqmlUom__0_x002e001_x0020gal_x005bUS_x005d_x002fbbl = 13, resqml2__ResqmlUom__0_x002e001_x0020gal_x005bUS_x005d_x002fft3 = 14, resqml2__ResqmlUom__0_x002e001_x0020gal_x005bUS_x005d_x002fgal_x005bUS_x005d = 15, resqml2__ResqmlUom__0_x002e001_x0020h_x002fft = 16, resqml2__ResqmlUom__0_x002e001_x0020kPa2_x002fcP = 17, resqml2__ResqmlUom__0_x002e001_x0020lbm_x002fbbl = 18, resqml2__ResqmlUom__0_x002e001_x0020lbm_x002fgal_x005bUK_x005d = 19, resqml2__ResqmlUom__0_x002e001_x0020lbm_x002fgal_x005bUS_x005d = 20, resqml2__ResqmlUom__0_x002e001_x0020psi_x002fft = 21, resqml2__ResqmlUom__0_x002e001_x0020pt_x005bUK_x005d_x002fbbl = 22, resqml2__ResqmlUom__0_x002e001_x0020seca = 23, resqml2__ResqmlUom__0_x002e01_x0020bbl_x002fbbl = 24, resqml2__ResqmlUom__0_x002e01_x0020dega_x002fft = 25, resqml2__ResqmlUom__0_x002e01_x0020degF_x002fft = 26, resqml2__ResqmlUom__0_x002e01_x0020dm3_x002fkm = 27, resqml2__ResqmlUom__0_x002e01_x0020ft_x002fft = 28, resqml2__ResqmlUom__0_x002e01_x0020grain_x002fft3 = 29, resqml2__ResqmlUom__0_x002e01_x0020L_x002fkg = 30, resqml2__ResqmlUom__0_x002e01_x0020L_x002fkm = 31, resqml2__ResqmlUom__0_x002e01_x0020lbf_x002fft = 32, resqml2__ResqmlUom__0_x002e01_x0020lbf_x002fft2 = 33, resqml2__ResqmlUom__0_x002e01_x0020lbm_x002fft2 = 34, resqml2__ResqmlUom__0_x002e01_x0020psi_x002fft = 35, resqml2__ResqmlUom__0_x002e1_x0020ft = 36, resqml2__ResqmlUom__0_x002e1_x0020ft_x005bUS_x005d = 37, resqml2__ResqmlUom__0_x002e1_x0020gal_x005bUS_x005d_x002fbbl = 38, resqml2__ResqmlUom__0_x002e1_x0020in = 39, resqml2__ResqmlUom__0_x002e1_x0020L_x002fbbl = 40, resqml2__ResqmlUom__0_x002e1_x0020lbm_x002fbbl = 41, resqml2__ResqmlUom__0_x002e1_x0020pt_x005bUS_x005d_x002fbbl = 42, resqml2__ResqmlUom__0_x002e1_x0020yd = 43, resqml2__ResqmlUom__1_x002f_x0028kg_x002es_x0029 = 44, resqml2__ResqmlUom__1_x002f16_x0020in = 45, resqml2__ResqmlUom__1_x002f2_x0020ft = 46, resqml2__ResqmlUom__1_x002f2_x0020ms = 47, resqml2__ResqmlUom__1_x002f30_x0020cm3_x002fmin = 48, resqml2__ResqmlUom__1_x002f30_x0020dega_x002fft = 49, resqml2__ResqmlUom__1_x002f30_x0020dega_x002fm = 50, resqml2__ResqmlUom__1_x002f30_x0020lbf_x002fm = 51, resqml2__ResqmlUom__1_x002f30_x0020m_x002fm = 52, resqml2__ResqmlUom__1_x002f30_x0020N_x002fm = 53, resqml2__ResqmlUom__1_x002f32_x0020in = 54, resqml2__ResqmlUom__1_x002f64_x0020in = 55, resqml2__ResqmlUom__1_x002fa = 56, resqml2__ResqmlUom__1_x002fangstrom = 57, resqml2__ResqmlUom__1_x002fbar = 58, resqml2__ResqmlUom__1_x002fbbl = 59, resqml2__ResqmlUom__1_x002fcm = 60, resqml2__ResqmlUom__1_x002fd = 61, resqml2__ResqmlUom__1_x002fdegC = 62, resqml2__ResqmlUom__1_x002fdegF = 63, resqml2__ResqmlUom__1_x002fdegR = 64, resqml2__ResqmlUom__1_x002fft = 65, resqml2__ResqmlUom__1_x002fft2 = 66, resqml2__ResqmlUom__1_x002fft3 = 67, resqml2__ResqmlUom__1_x002fg = 68, resqml2__ResqmlUom__1_x002fgal_x005bUK_x005d = 69, resqml2__ResqmlUom__1_x002fgal_x005bUS_x005d = 70, resqml2__ResqmlUom__1_x002fh = 71, resqml2__ResqmlUom__1_x002fH = 72, resqml2__ResqmlUom__1_x002fin = 73, resqml2__ResqmlUom__1_x002fK = 74, resqml2__ResqmlUom__1_x002fkg = 75, resqml2__ResqmlUom__1_x002fkm2 = 76, resqml2__ResqmlUom__1_x002fkPa = 77, resqml2__ResqmlUom__1_x002fL = 78, resqml2__ResqmlUom__1_x002flbf = 79, resqml2__ResqmlUom__1_x002flbm = 80, resqml2__ResqmlUom__1_x002fm = 81, resqml2__ResqmlUom__1_x002fm2 = 82, resqml2__ResqmlUom__1_x002fm3 = 83, resqml2__ResqmlUom__1_x002fmi = 84, resqml2__ResqmlUom__1_x002fmi2 = 85, resqml2__ResqmlUom__1_x002fmin = 86, resqml2__ResqmlUom__1_x002fmm = 87, resqml2__ResqmlUom__1_x002fms = 88, resqml2__ResqmlUom__1_x002fN = 89, resqml2__ResqmlUom__1_x002fnm = 90, resqml2__ResqmlUom__1_x002fPa = 91, resqml2__ResqmlUom__1_x002fpPa = 92, resqml2__ResqmlUom__1_x002fpsi = 93, resqml2__ResqmlUom__1_x002fs = 94, resqml2__ResqmlUom__1_x002fupsi = 95, resqml2__ResqmlUom__1_x002fus = 96, resqml2__ResqmlUom__1_x002fuV = 97, resqml2__ResqmlUom__1_x002fV = 98, resqml2__ResqmlUom__1_x002fwk = 99, resqml2__ResqmlUom__1_x002fyd = 100, resqml2__ResqmlUom__10_x0020ft = 101, resqml2__ResqmlUom__10_x0020in = 102, resqml2__ResqmlUom__10_x0020km = 103, resqml2__ResqmlUom__10_x0020kN = 104, resqml2__ResqmlUom__10_x0020Mg_x002fm3 = 105, resqml2__ResqmlUom__100_x0020ft = 106, resqml2__ResqmlUom__100_x0020ka_x005bt_x005d = 107, resqml2__ResqmlUom__100_x0020km = 108, resqml2__ResqmlUom__1000_x0020bbl = 109, resqml2__ResqmlUom__1000_x0020bbl_x002eft_x002fd = 110, resqml2__ResqmlUom__1000_x0020bbl_x002fd = 111, resqml2__ResqmlUom__1000_x0020ft = 112, resqml2__ResqmlUom__1000_x0020ft_x002fh = 113, resqml2__ResqmlUom__1000_x0020ft_x002fs = 114, resqml2__ResqmlUom__1000_x0020ft3 = 115, resqml2__ResqmlUom__1000_x0020ft3_x002f_x0028d_x002eft_x0029 = 116, resqml2__ResqmlUom__1000_x0020ft3_x002f_x0028psi_x002ed_x0029 = 117, resqml2__ResqmlUom__1000_x0020ft3_x002fbbl = 118, resqml2__ResqmlUom__1000_x0020ft3_x002fd = 119, resqml2__ResqmlUom__1000_x0020gal_x005bUK_x005d = 120, resqml2__ResqmlUom__1000_x0020gal_x005bUS_x005d = 121, resqml2__ResqmlUom__1000_x0020lbf_x002eft = 122, resqml2__ResqmlUom__1000_x0020m3 = 123, resqml2__ResqmlUom__1000_x0020m3_x002f_x0028d_x002em_x0029 = 124, resqml2__ResqmlUom__1000_x0020m3_x002f_x0028h_x002em_x0029 = 125, resqml2__ResqmlUom__1000_x0020m3_x002fd = 126, resqml2__ResqmlUom__1000_x0020m3_x002fh = 127, resqml2__ResqmlUom__1000_x0020m3_x002fm3 = 128, resqml2__ResqmlUom__1000_x0020m4_x002fd = 129, resqml2__ResqmlUom__1E12_x0020ft3 = 130, resqml2__ResqmlUom__1E6_x0020_x0028ft3_x002fd_x0029_x002f_x0028bbl_x002fd_x0029 = 131, resqml2__ResqmlUom__1E_6_x0020acre_x002eft_x002fbbl = 132, resqml2__ResqmlUom__1E6_x0020bbl = 133, resqml2__ResqmlUom__1E6_x0020bbl_x002f_x0028acre_x002eft_x0029 = 134, resqml2__ResqmlUom__1E6_x0020bbl_x002facre = 135, resqml2__ResqmlUom__1E6_x0020bbl_x002fd = 136, resqml2__ResqmlUom__1E_6_x0020bbl_x002fft3 = 137, resqml2__ResqmlUom__1E_6_x0020bbl_x002fm3 = 138, resqml2__ResqmlUom__1E6_x0020Btu_x005bIT_x005d = 139, resqml2__ResqmlUom__1E6_x0020Btu_x005bIT_x005d_x002fh = 140, resqml2__ResqmlUom__1E6_x0020ft3 = 141, resqml2__ResqmlUom__1E6_x0020ft3_x002f_x0028acre_x002eft_x0029 = 142, resqml2__ResqmlUom__1E6_x0020ft3_x002fbbl = 143, resqml2__ResqmlUom__1E6_x0020ft3_x002fd = 144, resqml2__ResqmlUom__1E_6_x0020gal_x005bUS_x005d = 145, resqml2__ResqmlUom__1E6_x0020lbm_x002fa = 146, resqml2__ResqmlUom__1E6_x0020m3 = 147, resqml2__ResqmlUom__1E_6_x0020m3_x002f_x0028m3_x002edegC_x0029 = 148, resqml2__ResqmlUom__1E_6_x0020m3_x002f_x0028m3_x002edegF_x0029 = 149, resqml2__ResqmlUom__1E6_x0020m3_x002fd = 150, resqml2__ResqmlUom__1E_9_x00201_x002fft = 151, resqml2__ResqmlUom__1E9_x0020bbl = 152, resqml2__ResqmlUom__1E9_x0020ft3 = 153, resqml2__ResqmlUom__30_x0020ft = 154, resqml2__ResqmlUom__30_x0020m = 155, resqml2__ResqmlUom__a = 156, resqml2__ResqmlUom__A = 157, resqml2__ResqmlUom__A_x002eh = 158, resqml2__ResqmlUom__A_x002em2 = 159, resqml2__ResqmlUom__A_x002es = 160, resqml2__ResqmlUom__A_x002es_x002fkg = 161, resqml2__ResqmlUom__A_x002es_x002fm3 = 162, resqml2__ResqmlUom__A_x002fcm2 = 163, resqml2__ResqmlUom__A_x002fft2 = 164, resqml2__ResqmlUom__A_x002fm = 165, resqml2__ResqmlUom__A_x002fm2 = 166, resqml2__ResqmlUom__A_x002fmm = 167, resqml2__ResqmlUom__A_x002fmm2 = 168, resqml2__ResqmlUom__a_x005bt_x005d = 169, resqml2__ResqmlUom__acre = 170, resqml2__ResqmlUom__acre_x002eft = 171, resqml2__ResqmlUom__ag = 172, resqml2__ResqmlUom__aJ = 173, resqml2__ResqmlUom__angstrom = 174, resqml2__ResqmlUom__at = 175, resqml2__ResqmlUom__atm = 176, resqml2__ResqmlUom__atm_x002fft = 177, resqml2__ResqmlUom__atm_x002fh = 178, resqml2__ResqmlUom__atm_x002fhm = 179, resqml2__ResqmlUom__atm_x002fm = 180, resqml2__ResqmlUom__B = 181, resqml2__ResqmlUom__b = 182, resqml2__ResqmlUom__B_x002eW = 183, resqml2__ResqmlUom__b_x002fcm3 = 184, resqml2__ResqmlUom__B_x002fm = 185, resqml2__ResqmlUom__B_x002fO = 186, resqml2__ResqmlUom__bar = 187, resqml2__ResqmlUom__bar_x002fh = 188, resqml2__ResqmlUom__bar_x002fkm = 189, resqml2__ResqmlUom__bar_x002fm = 190, resqml2__ResqmlUom__bar2 = 191, resqml2__ResqmlUom__bar2_x002fcP = 192, resqml2__ResqmlUom__bbl = 193, resqml2__ResqmlUom__bbl_x002f_x0028acre_x002eft_x0029 = 194, resqml2__ResqmlUom__bbl_x002f_x0028d_x002eacre_x002eft_x0029 = 195, resqml2__ResqmlUom__bbl_x002f_x0028d_x002eft_x0029 = 196, resqml2__ResqmlUom__bbl_x002f_x0028ft_x002epsi_x002ed_x0029 = 197, resqml2__ResqmlUom__bbl_x002f_x0028kPa_x002ed_x0029 = 198, resqml2__ResqmlUom__bbl_x002f_x0028psi_x002ed_x0029 = 199, resqml2__ResqmlUom__bbl_x002facre = 200, resqml2__ResqmlUom__bbl_x002fbbl = 201, resqml2__ResqmlUom__bbl_x002fd = 202, resqml2__ResqmlUom__bbl_x002fd2 = 203, resqml2__ResqmlUom__bbl_x002fft = 204, resqml2__ResqmlUom__bbl_x002fft3 = 205, resqml2__ResqmlUom__bbl_x002fh = 206, resqml2__ResqmlUom__bbl_x002fh2 = 207, resqml2__ResqmlUom__bbl_x002fin = 208, resqml2__ResqmlUom__bbl_x002fm3 = 209, resqml2__ResqmlUom__bbl_x002fmi = 210, resqml2__ResqmlUom__bbl_x002fmin = 211, resqml2__ResqmlUom__bbl_x002fpsi = 212, resqml2__ResqmlUom__bbl_x002fton_x005bUK_x005d = 213, resqml2__ResqmlUom__bbl_x002fton_x005bUS_x005d = 214, resqml2__ResqmlUom__Bd = 215, resqml2__ResqmlUom__bit = 216, resqml2__ResqmlUom__bit_x002fs = 217, resqml2__ResqmlUom__Bq = 218, resqml2__ResqmlUom__Bq_x002fkg = 219, resqml2__ResqmlUom__Btu_x005bIT_x005d = 220, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002ein_x002f_x0028h_x002eft2_x002edegF_x0029 = 221, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft_x002edegF_x0029 = 222, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft2_x0029 = 223, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft2_x002edegF_x0029 = 224, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft2_x002edegR_x0029 = 225, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft3_x0029 = 226, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002eft3_x002edegF_x0029 = 227, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028h_x002em2_x002edegC_x0029 = 228, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028hp_x002eh_x0029 = 229, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028lbm_x002edegF_x0029 = 230, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028lbm_x002edegR_x0029 = 231, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028lbmol_x002edegF_x0029 = 232, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028s_x002eft2_x0029 = 233, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028s_x002eft2_x002edegF_x0029 = 234, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028s_x002eft3_x0029 = 235, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002f_x0028s_x002eft3_x002edegF_x0029 = 236, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002fbbl = 237, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002fft3 = 238, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002fgal_x005bUK_x005d = 239, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002fgal_x005bUS_x005d = 240, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002fh = 241, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002flbm = 242, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002flbmol = 243, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002fmin = 244, resqml2__ResqmlUom__Btu_x005bIT_x005d_x002fs = 245, resqml2__ResqmlUom__Btu_x005bth_x005d = 246, resqml2__ResqmlUom__Btu_x005bUK_x005d = 247, resqml2__ResqmlUom__byte = 248, resqml2__ResqmlUom__byte_x002fs = 249, resqml2__ResqmlUom__C = 250, resqml2__ResqmlUom__C_x002em = 251, resqml2__ResqmlUom__C_x002fcm2 = 252, resqml2__ResqmlUom__C_x002fcm3 = 253, resqml2__ResqmlUom__C_x002fg = 254, resqml2__ResqmlUom__C_x002fkg = 255, resqml2__ResqmlUom__C_x002fm2 = 256, resqml2__ResqmlUom__C_x002fm3 = 257, resqml2__ResqmlUom__C_x002fmm2 = 258, resqml2__ResqmlUom__C_x002fmm3 = 259, resqml2__ResqmlUom__cA = 260, resqml2__ResqmlUom__ca = 261, resqml2__ResqmlUom__cal_x005bIT_x005d = 262, resqml2__ResqmlUom__cal_x005bth_x005d = 263, resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028g_x002eK_x0029 = 264, resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028h_x002ecm_x002edegC_x0029 = 265, resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028h_x002ecm2_x0029 = 266, resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028h_x002ecm2_x002edegC_x0029 = 267, resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028h_x002ecm3_x0029 = 268, resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028mol_x002edegC_x0029 = 269, resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028s_x002ecm_x002edegC_x0029 = 270, resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028s_x002ecm2_x002edegC_x0029 = 271, resqml2__ResqmlUom__cal_x005bth_x005d_x002f_x0028s_x002ecm3_x0029 = 272, resqml2__ResqmlUom__cal_x005bth_x005d_x002fcm3 = 273, resqml2__ResqmlUom__cal_x005bth_x005d_x002fg = 274, resqml2__ResqmlUom__cal_x005bth_x005d_x002fh = 275, resqml2__ResqmlUom__cal_x005bth_x005d_x002fkg = 276, resqml2__ResqmlUom__cal_x005bth_x005d_x002flbm = 277, resqml2__ResqmlUom__cal_x005bth_x005d_x002fmL = 278, resqml2__ResqmlUom__cal_x005bth_x005d_x002fmm3 = 279, resqml2__ResqmlUom__cC = 280, resqml2__ResqmlUom__ccal_x005bth_x005d = 281, resqml2__ResqmlUom__ccgr = 282, resqml2__ResqmlUom__cd = 283, resqml2__ResqmlUom__cd_x002fm2 = 284, resqml2__ResqmlUom__cEuc = 285, resqml2__ResqmlUom__ceV = 286, resqml2__ResqmlUom__cF = 287, resqml2__ResqmlUom__cg = 288, resqml2__ResqmlUom__cgauss = 289, resqml2__ResqmlUom__cgr = 290, resqml2__ResqmlUom__cGy = 291, resqml2__ResqmlUom__cH = 292, resqml2__ResqmlUom__chain = 293, resqml2__ResqmlUom__chain_x005bBnA_x005d = 294, resqml2__ResqmlUom__chain_x005bBnB_x005d = 295, resqml2__ResqmlUom__chain_x005bCla_x005d = 296, resqml2__ResqmlUom__chain_x005bInd37_x005d = 297, resqml2__ResqmlUom__chain_x005bSe_x005d = 298, resqml2__ResqmlUom__chain_x005bSeT_x005d = 299, resqml2__ResqmlUom__chain_x005bUS_x005d = 300, resqml2__ResqmlUom__cHz = 301, resqml2__ResqmlUom__Ci = 302, resqml2__ResqmlUom__cJ = 303, resqml2__ResqmlUom__cm = 304, resqml2__ResqmlUom__cm_x002fa = 305, resqml2__ResqmlUom__cm_x002fs = 306, resqml2__ResqmlUom__cm_x002fs2 = 307, resqml2__ResqmlUom__cm2 = 308, resqml2__ResqmlUom__cm2_x002fg = 309, resqml2__ResqmlUom__cm2_x002fs = 310, resqml2__ResqmlUom__cm3 = 311, resqml2__ResqmlUom__cm3_x002fcm3 = 312, resqml2__ResqmlUom__cm3_x002fg = 313, resqml2__ResqmlUom__cm3_x002fh = 314, resqml2__ResqmlUom__cm3_x002fL = 315, resqml2__ResqmlUom__cm3_x002fm3 = 316, resqml2__ResqmlUom__cm3_x002fmin = 317, resqml2__ResqmlUom__cm3_x002fs = 318, resqml2__ResqmlUom__cm4 = 319, resqml2__ResqmlUom__cmH2O_x005b4degC_x005d = 320, resqml2__ResqmlUom__cN = 321, resqml2__ResqmlUom__cohm = 322, resqml2__ResqmlUom__cP = 323, resqml2__ResqmlUom__cPa = 324, resqml2__ResqmlUom__crd = 325, resqml2__ResqmlUom__cs = 326, resqml2__ResqmlUom__cS = 327, resqml2__ResqmlUom__cSt = 328, resqml2__ResqmlUom__ct = 329, resqml2__ResqmlUom__cT = 330, resqml2__ResqmlUom__cu = 331, resqml2__ResqmlUom__cV = 332, resqml2__ResqmlUom__cW = 333, resqml2__ResqmlUom__cWb = 334, resqml2__ResqmlUom__cwt_x005bUK_x005d = 335, resqml2__ResqmlUom__cwt_x005bUS_x005d = 336, resqml2__ResqmlUom__d = 337, resqml2__ResqmlUom__D = 338, resqml2__ResqmlUom__D_x002eft = 339, resqml2__ResqmlUom__D_x002em = 340, resqml2__ResqmlUom__D_x002f_x0028Pa_x002es_x0029 = 341, resqml2__ResqmlUom__d_x002fbbl = 342, resqml2__ResqmlUom__D_x002fcP = 343, resqml2__ResqmlUom__d_x002fft3 = 344, resqml2__ResqmlUom__d_x002fm3 = 345, resqml2__ResqmlUom__D_x005bAPI_x005d = 346, resqml2__ResqmlUom__dA = 347, resqml2__ResqmlUom__dam = 348, resqml2__ResqmlUom__daN = 349, resqml2__ResqmlUom__daN_x002em = 350, resqml2__ResqmlUom__dAPI = 351, resqml2__ResqmlUom__dB = 352, resqml2__ResqmlUom__dB_x002emW = 353, resqml2__ResqmlUom__dB_x002eMW = 354, resqml2__ResqmlUom__dB_x002eW = 355, resqml2__ResqmlUom__dB_x002fft = 356, resqml2__ResqmlUom__dB_x002fkm = 357, resqml2__ResqmlUom__dB_x002fm = 358, resqml2__ResqmlUom__dB_x002fO = 359, resqml2__ResqmlUom__dC = 360, resqml2__ResqmlUom__dcal_x005bth_x005d = 361, resqml2__ResqmlUom__dega = 362, resqml2__ResqmlUom__dega_x002fft = 363, resqml2__ResqmlUom__dega_x002fh = 364, resqml2__ResqmlUom__dega_x002fm = 365, resqml2__ResqmlUom__dega_x002fmin = 366, resqml2__ResqmlUom__dega_x002fs = 367, resqml2__ResqmlUom__degC = 368, resqml2__ResqmlUom__degC_x002em2_x002eh_x002fkcal_x005bth_x005d = 369, resqml2__ResqmlUom__degC_x002fft = 370, resqml2__ResqmlUom__degC_x002fh = 371, resqml2__ResqmlUom__degC_x002fhm = 372, resqml2__ResqmlUom__degC_x002fkm = 373, resqml2__ResqmlUom__degC_x002fkPa = 374, resqml2__ResqmlUom__degC_x002fm = 375, resqml2__ResqmlUom__degC_x002fmin = 376, resqml2__ResqmlUom__degC_x002fs = 377, resqml2__ResqmlUom__degF = 378, resqml2__ResqmlUom__degF_x002eft2_x002eh_x002fBtu_x005bIT_x005d = 379, resqml2__ResqmlUom__degF_x002fft = 380, resqml2__ResqmlUom__degF_x002fh = 381, resqml2__ResqmlUom__degF_x002fm = 382, resqml2__ResqmlUom__degF_x002fmin = 383, resqml2__ResqmlUom__degF_x002fpsi = 384, resqml2__ResqmlUom__degF_x002fs = 385, resqml2__ResqmlUom__degR = 386, resqml2__ResqmlUom__dEuc = 387, resqml2__ResqmlUom__deV = 388, resqml2__ResqmlUom__dF = 389, resqml2__ResqmlUom__dgauss = 390, resqml2__ResqmlUom__dGy = 391, resqml2__ResqmlUom__dH = 392, resqml2__ResqmlUom__dHz = 393, resqml2__ResqmlUom__dJ = 394, resqml2__ResqmlUom__dm = 395, resqml2__ResqmlUom__dm_x002fs = 396, resqml2__ResqmlUom__dm3 = 397, resqml2__ResqmlUom__dm3_x002f_x0028kW_x002eh_x0029 = 398, resqml2__ResqmlUom__dm3_x002fkg = 399, resqml2__ResqmlUom__dm3_x002fkmol = 400, resqml2__ResqmlUom__dm3_x002fm = 401, resqml2__ResqmlUom__dm3_x002fm3 = 402, resqml2__ResqmlUom__dm3_x002fMJ = 403, resqml2__ResqmlUom__dm3_x002fs = 404, resqml2__ResqmlUom__dm3_x002fs2 = 405, resqml2__ResqmlUom__dm3_x002ft = 406, resqml2__ResqmlUom__dN = 407, resqml2__ResqmlUom__dN_x002em = 408, resqml2__ResqmlUom__dohm = 409, resqml2__ResqmlUom__dP = 410, resqml2__ResqmlUom__dPa = 411, resqml2__ResqmlUom__drd = 412, resqml2__ResqmlUom__ds = 413, resqml2__ResqmlUom__dS = 414, resqml2__ResqmlUom__dT = 415, resqml2__ResqmlUom__dV = 416, resqml2__ResqmlUom__dW = 417, resqml2__ResqmlUom__dWb = 418, resqml2__ResqmlUom__dyne = 419, resqml2__ResqmlUom__dyne_x002ecm2 = 420, resqml2__ResqmlUom__dyne_x002es_x002fcm2 = 421, resqml2__ResqmlUom__dyne_x002fcm = 422, resqml2__ResqmlUom__dyne_x002fcm2 = 423, resqml2__ResqmlUom__EA = 424, resqml2__ResqmlUom__Ea_x005bt_x005d = 425, resqml2__ResqmlUom__EC = 426, resqml2__ResqmlUom__Ecal_x005bth_x005d = 427, resqml2__ResqmlUom__EEuc = 428, resqml2__ResqmlUom__EeV = 429, resqml2__ResqmlUom__EF = 430, resqml2__ResqmlUom__Eg = 431, resqml2__ResqmlUom__Egauss = 432, resqml2__ResqmlUom__EGy = 433, resqml2__ResqmlUom__EH = 434, resqml2__ResqmlUom__EHz = 435, resqml2__ResqmlUom__EJ = 436, resqml2__ResqmlUom__EJ_x002fa = 437, resqml2__ResqmlUom__Em = 438, resqml2__ResqmlUom__EN = 439, resqml2__ResqmlUom__Eohm = 440, resqml2__ResqmlUom__EP = 441, resqml2__ResqmlUom__EPa = 442, resqml2__ResqmlUom__Erd = 443, resqml2__ResqmlUom__erg = 444, resqml2__ResqmlUom__erg_x002fa = 445, resqml2__ResqmlUom__erg_x002fcm2 = 446, resqml2__ResqmlUom__erg_x002fcm3 = 447, resqml2__ResqmlUom__erg_x002fg = 448, resqml2__ResqmlUom__erg_x002fkg = 449, resqml2__ResqmlUom__erg_x002fm3 = 450, resqml2__ResqmlUom__ES = 451, resqml2__ResqmlUom__ET = 452, resqml2__ResqmlUom__Euc = 453, resqml2__ResqmlUom__eV = 454, resqml2__ResqmlUom__EW = 455, resqml2__ResqmlUom__EWb = 456, resqml2__ResqmlUom__F = 457, resqml2__ResqmlUom__F_x002fm = 458, resqml2__ResqmlUom__fA = 459, resqml2__ResqmlUom__fa = 460, resqml2__ResqmlUom__fathom = 461, resqml2__ResqmlUom__fC = 462, resqml2__ResqmlUom__fcal_x005bth_x005d = 463, resqml2__ResqmlUom__fEuc = 464, resqml2__ResqmlUom__feV = 465, resqml2__ResqmlUom__fF = 466, resqml2__ResqmlUom__fg = 467, resqml2__ResqmlUom__fgauss = 468, resqml2__ResqmlUom__fGy = 469, resqml2__ResqmlUom__fH = 470, resqml2__ResqmlUom__fHz = 471, resqml2__ResqmlUom__fJ = 472, resqml2__ResqmlUom__floz_x005bUK_x005d = 473, resqml2__ResqmlUom__floz_x005bUS_x005d = 474, resqml2__ResqmlUom__fm = 475, resqml2__ResqmlUom__fN = 476, resqml2__ResqmlUom__fohm = 477, resqml2__ResqmlUom__footcandle = 478, resqml2__ResqmlUom__footcandle_x002es = 479, resqml2__ResqmlUom__fP = 480, resqml2__ResqmlUom__fPa = 481, resqml2__ResqmlUom__frd = 482, resqml2__ResqmlUom__fS = 483, resqml2__ResqmlUom__fT = 484, resqml2__ResqmlUom__ft = 485, resqml2__ResqmlUom__ft_x002fbbl = 486, resqml2__ResqmlUom__ft_x002fd = 487, resqml2__ResqmlUom__ft_x002fdegF = 488, resqml2__ResqmlUom__ft_x002fft = 489, resqml2__ResqmlUom__ft_x002fft3 = 490, resqml2__ResqmlUom__ft_x002fgal_x005bUS_x005d = 491, resqml2__ResqmlUom__ft_x002fh = 492, resqml2__ResqmlUom__ft_x002fin = 493, resqml2__ResqmlUom__ft_x002flbm = 494, resqml2__ResqmlUom__ft_x002fm = 495, resqml2__ResqmlUom__ft_x002fmi = 496, resqml2__ResqmlUom__ft_x002fmin = 497, resqml2__ResqmlUom__ft_x002fms = 498, resqml2__ResqmlUom__ft_x002fpsi = 499, resqml2__ResqmlUom__ft_x002fs = 500, resqml2__ResqmlUom__ft_x002fs2 = 501, resqml2__ResqmlUom__ft_x002fus = 502, resqml2__ResqmlUom__ft_x005bBnA_x005d = 503, resqml2__ResqmlUom__ft_x005bBnB_x005d = 504, resqml2__ResqmlUom__ft_x005bBr36_x005d = 505, resqml2__ResqmlUom__ft_x005bBr65_x005d = 506, resqml2__ResqmlUom__ft_x005bCla_x005d = 507, resqml2__ResqmlUom__ft_x005bGC_x005d = 508, resqml2__ResqmlUom__ft_x005bInd_x005d = 509, resqml2__ResqmlUom__ft_x005bInd37_x005d = 510, resqml2__ResqmlUom__ft_x005bInd62_x005d = 511, resqml2__ResqmlUom__ft_x005bInd75_x005d = 512, resqml2__ResqmlUom__ft_x005bSe_x005d = 513, resqml2__ResqmlUom__ft_x005bSeT_x005d = 514, resqml2__ResqmlUom__ft_x005bUS_x005d = 515, resqml2__ResqmlUom__ft2 = 516, resqml2__ResqmlUom__ft2_x002fh = 517, resqml2__ResqmlUom__ft2_x002fin3 = 518, resqml2__ResqmlUom__ft2_x002flbm = 519, resqml2__ResqmlUom__ft2_x002fs = 520, resqml2__ResqmlUom__ft3 = 521, resqml2__ResqmlUom__ft3_x002f_x0028d_x002eft_x0029 = 522, resqml2__ResqmlUom__ft3_x002f_x0028ft_x002epsi_x002ed_x0029 = 523, resqml2__ResqmlUom__ft3_x002f_x0028min_x002eft2_x0029 = 524, resqml2__ResqmlUom__ft3_x002f_x0028s_x002eft2_x0029 = 525, resqml2__ResqmlUom__ft3_x002fbbl = 526, resqml2__ResqmlUom__ft3_x002fd = 527, resqml2__ResqmlUom__ft3_x002fd2 = 528, resqml2__ResqmlUom__ft3_x002fft = 529, resqml2__ResqmlUom__ft3_x002fft2 = 530, resqml2__ResqmlUom__ft3_x002fft3 = 531, resqml2__ResqmlUom__ft3_x002fh = 532, resqml2__ResqmlUom__ft3_x002fh2 = 533, resqml2__ResqmlUom__ft3_x002fkg = 534, resqml2__ResqmlUom__ft3_x002flbm = 535, resqml2__ResqmlUom__ft3_x002flbmol = 536, resqml2__ResqmlUom__ft3_x002fmin = 537, resqml2__ResqmlUom__ft3_x002fmin2 = 538, resqml2__ResqmlUom__ft3_x002frad = 539, resqml2__ResqmlUom__ft3_x002fs = 540, resqml2__ResqmlUom__ft3_x002fs2 = 541, resqml2__ResqmlUom__ft3_x002fsack_x005b94lbm_x005d = 542, resqml2__ResqmlUom__fur_x005bUS_x005d = 543, resqml2__ResqmlUom__fV = 544, resqml2__ResqmlUom__fW = 545, resqml2__ResqmlUom__fWb = 546, resqml2__ResqmlUom__g = 547, resqml2__ResqmlUom__g_x002eft_x002f_x0028cm3_x002es_x0029 = 548, resqml2__ResqmlUom__g_x002em_x002f_x0028cm3_x002es_x0029 = 549, resqml2__ResqmlUom__g_x002fcm3 = 550, resqml2__ResqmlUom__g_x002fcm4 = 551, resqml2__ResqmlUom__g_x002fdm3 = 552, resqml2__ResqmlUom__g_x002fgal_x005bUK_x005d = 553, resqml2__ResqmlUom__g_x002fgal_x005bUS_x005d = 554, resqml2__ResqmlUom__g_x002fkg = 555, resqml2__ResqmlUom__g_x002fL = 556, resqml2__ResqmlUom__g_x002fm3 = 557, resqml2__ResqmlUom__g_x002fmol = 558, resqml2__ResqmlUom__g_x002fs = 559, resqml2__ResqmlUom__g_x002ft = 560, resqml2__ResqmlUom__GA = 561, resqml2__ResqmlUom__Ga_x005bt_x005d = 562, resqml2__ResqmlUom__Gal = 563, resqml2__ResqmlUom__gal_x005bUK_x005d = 564, resqml2__ResqmlUom__gal_x005bUK_x005d_x002f_x0028h_x002eft_x0029 = 565, resqml2__ResqmlUom__gal_x005bUK_x005d_x002f_x0028h_x002eft2_x0029 = 566, resqml2__ResqmlUom__gal_x005bUK_x005d_x002f_x0028h_x002ein_x0029 = 567, resqml2__ResqmlUom__gal_x005bUK_x005d_x002f_x0028h_x002ein2_x0029 = 568, resqml2__ResqmlUom__gal_x005bUK_x005d_x002f_x0028min_x002eft_x0029 = 569, resqml2__ResqmlUom__gal_x005bUK_x005d_x002f_x0028min_x002eft2_x0029 = 570, resqml2__ResqmlUom__gal_x005bUK_x005d_x002fd = 571, resqml2__ResqmlUom__gal_x005bUK_x005d_x002fft3 = 572, resqml2__ResqmlUom__gal_x005bUK_x005d_x002fh = 573, resqml2__ResqmlUom__gal_x005bUK_x005d_x002fh2 = 574, resqml2__ResqmlUom__gal_x005bUK_x005d_x002flbm = 575, resqml2__ResqmlUom__gal_x005bUK_x005d_x002fmi = 576, resqml2__ResqmlUom__gal_x005bUK_x005d_x002fmin = 577, resqml2__ResqmlUom__gal_x005bUK_x005d_x002fmin2 = 578, resqml2__ResqmlUom__gal_x005bUS_x005d = 579, resqml2__ResqmlUom__gal_x005bUS_x005d_x002f_x0028h_x002eft_x0029 = 580, resqml2__ResqmlUom__gal_x005bUS_x005d_x002f_x0028h_x002eft2_x0029 = 581, resqml2__ResqmlUom__gal_x005bUS_x005d_x002f_x0028h_x002ein_x0029 = 582, resqml2__ResqmlUom__gal_x005bUS_x005d_x002f_x0028h_x002ein2_x0029 = 583, resqml2__ResqmlUom__gal_x005bUS_x005d_x002f_x0028min_x002eft_x0029 = 584, resqml2__ResqmlUom__gal_x005bUS_x005d_x002f_x0028min_x002eft2_x0029 = 585, resqml2__ResqmlUom__gal_x005bUS_x005d_x002fbbl = 586, resqml2__ResqmlUom__gal_x005bUS_x005d_x002fd = 587, resqml2__ResqmlUom__gal_x005bUS_x005d_x002fft = 588, resqml2__ResqmlUom__gal_x005bUS_x005d_x002fft3 = 589, resqml2__ResqmlUom__gal_x005bUS_x005d_x002fh = 590, resqml2__ResqmlUom__gal_x005bUS_x005d_x002fh2 = 591, resqml2__ResqmlUom__gal_x005bUS_x005d_x002flbm = 592, resqml2__ResqmlUom__gal_x005bUS_x005d_x002fmi = 593, resqml2__ResqmlUom__gal_x005bUS_x005d_x002fmin = 594, resqml2__ResqmlUom__gal_x005bUS_x005d_x002fmin2 = 595, resqml2__ResqmlUom__gal_x005bUS_x005d_x002fsack_x005b94lbm_x005d = 596, resqml2__ResqmlUom__gal_x005bUS_x005d_x002fton_x005bUK_x005d = 597, resqml2__ResqmlUom__gal_x005bUS_x005d_x002fton_x005bUS_x005d = 598, resqml2__ResqmlUom__gAPI = 599, resqml2__ResqmlUom__gauss = 600, resqml2__ResqmlUom__gauss_x002fcm = 601, resqml2__ResqmlUom__GBq = 602, resqml2__ResqmlUom__GC = 603, resqml2__ResqmlUom__Gcal_x005bth_x005d = 604, resqml2__ResqmlUom__GEuc = 605, resqml2__ResqmlUom__GeV = 606, resqml2__ResqmlUom__GF = 607, resqml2__ResqmlUom__gf = 608, resqml2__ResqmlUom__Gg = 609, resqml2__ResqmlUom__Ggauss = 610, resqml2__ResqmlUom__GGy = 611, resqml2__ResqmlUom__GH = 612, resqml2__ResqmlUom__GHz = 613, resqml2__ResqmlUom__GJ = 614, resqml2__ResqmlUom__Gm = 615, resqml2__ResqmlUom__GN = 616, resqml2__ResqmlUom__gn = 617, resqml2__ResqmlUom__Gohm = 618, resqml2__ResqmlUom__gon = 619, resqml2__ResqmlUom__GP = 620, resqml2__ResqmlUom__GPa = 621, resqml2__ResqmlUom__GPa_x002fcm = 622, resqml2__ResqmlUom__GPa2 = 623, resqml2__ResqmlUom__grain = 624, resqml2__ResqmlUom__grain_x002fft3 = 625, resqml2__ResqmlUom__grain_x002fgal_x005bUS_x005d = 626, resqml2__ResqmlUom__Grd = 627, resqml2__ResqmlUom__GS = 628, resqml2__ResqmlUom__GT = 629, resqml2__ResqmlUom__GV = 630, resqml2__ResqmlUom__GW = 631, resqml2__ResqmlUom__GW_x002eh = 632, resqml2__ResqmlUom__GWb = 633, resqml2__ResqmlUom__Gy = 634, resqml2__ResqmlUom__h = 635, resqml2__ResqmlUom__H = 636, resqml2__ResqmlUom__h_x002fft3 = 637, resqml2__ResqmlUom__h_x002fkm = 638, resqml2__ResqmlUom__H_x002fm = 639, resqml2__ResqmlUom__h_x002fm3 = 640, resqml2__ResqmlUom__ha = 641, resqml2__ResqmlUom__ha_x002em = 642, resqml2__ResqmlUom__hbar = 643, resqml2__ResqmlUom__hg = 644, resqml2__ResqmlUom__hL = 645, resqml2__ResqmlUom__hm = 646, resqml2__ResqmlUom__hN = 647, resqml2__ResqmlUom__hp = 648, resqml2__ResqmlUom__hp_x002eh = 649, resqml2__ResqmlUom__hp_x002eh_x002fbbl = 650, resqml2__ResqmlUom__hp_x002eh_x002flbm = 651, resqml2__ResqmlUom__hp_x002fft3 = 652, resqml2__ResqmlUom__hp_x002fin2 = 653, resqml2__ResqmlUom__hp_x005belec_x005d = 654, resqml2__ResqmlUom__hp_x005bhyd_x005d = 655, resqml2__ResqmlUom__hp_x005bhyd_x005d_x002fin2 = 656, resqml2__ResqmlUom__hp_x005bmetric_x005d = 657, resqml2__ResqmlUom__hp_x005bmetric_x005d_x002eh = 658, resqml2__ResqmlUom__hs = 659, resqml2__ResqmlUom__Hz = 660, resqml2__ResqmlUom__in = 661, resqml2__ResqmlUom__in_x002f_x0028in_x002edegF_x0029 = 662, resqml2__ResqmlUom__in_x002fa = 663, resqml2__ResqmlUom__in_x002fmin = 664, resqml2__ResqmlUom__in_x002fs = 665, resqml2__ResqmlUom__in_x002fs2 = 666, resqml2__ResqmlUom__in_x005bUS_x005d = 667, resqml2__ResqmlUom__in2 = 668, resqml2__ResqmlUom__in2_x002fft2 = 669, resqml2__ResqmlUom__in2_x002fin2 = 670, resqml2__ResqmlUom__in2_x002fs = 671, resqml2__ResqmlUom__in3 = 672, resqml2__ResqmlUom__in3_x002fft = 673, resqml2__ResqmlUom__in4 = 674, resqml2__ResqmlUom__inH2O_x005b39degF_x005d = 675, resqml2__ResqmlUom__inH2O_x005b60degF_x005d = 676, resqml2__ResqmlUom__inHg_x005b32degF_x005d = 677, resqml2__ResqmlUom__inHg_x005b60degF_x005d = 678, resqml2__ResqmlUom__J = 679, resqml2__ResqmlUom__J_x002em_x002f_x0028s_x002em2_x002eK_x0029 = 680, resqml2__ResqmlUom__J_x002em_x002fm2 = 681, resqml2__ResqmlUom__J_x002f_x0028g_x002eK_x0029 = 682, resqml2__ResqmlUom__J_x002f_x0028kg_x002eK_x0029 = 683, resqml2__ResqmlUom__J_x002f_x0028mol_x002eK_x0029 = 684, resqml2__ResqmlUom__J_x002f_x0028s_x002em2_x002edegC_x0029 = 685, resqml2__ResqmlUom__J_x002fcm2 = 686, resqml2__ResqmlUom__J_x002fdm3 = 687, resqml2__ResqmlUom__J_x002fg = 688, resqml2__ResqmlUom__J_x002fK = 689, resqml2__ResqmlUom__J_x002fkg = 690, resqml2__ResqmlUom__J_x002fm = 691, resqml2__ResqmlUom__J_x002fm2 = 692, resqml2__ResqmlUom__J_x002fm3 = 693, resqml2__ResqmlUom__J_x002fmol = 694, resqml2__ResqmlUom__J_x002fs = 695, resqml2__ResqmlUom__K = 696, resqml2__ResqmlUom__K_x002em2_x002fkW = 697, resqml2__ResqmlUom__K_x002em2_x002fW = 698, resqml2__ResqmlUom__K_x002fkm = 699, resqml2__ResqmlUom__K_x002fm = 700, resqml2__ResqmlUom__K_x002fPa = 701, resqml2__ResqmlUom__K_x002fs = 702, resqml2__ResqmlUom__K_x002fW = 703, resqml2__ResqmlUom__kA = 704, resqml2__ResqmlUom__ka_x005bt_x005d = 705, resqml2__ResqmlUom__kC = 706, resqml2__ResqmlUom__kcal_x005bth_x005d = 707, resqml2__ResqmlUom__kcal_x005bth_x005d_x002em_x002fcm2 = 708, resqml2__ResqmlUom__kcal_x005bth_x005d_x002f_x0028h_x002em_x002edegC_x0029 = 709, resqml2__ResqmlUom__kcal_x005bth_x005d_x002f_x0028h_x002em2_x002edegC_x0029 = 710, resqml2__ResqmlUom__kcal_x005bth_x005d_x002f_x0028kg_x002edegC_x0029 = 711, resqml2__ResqmlUom__kcal_x005bth_x005d_x002fcm3 = 712, resqml2__ResqmlUom__kcal_x005bth_x005d_x002fg = 713, resqml2__ResqmlUom__kcal_x005bth_x005d_x002fh = 714, resqml2__ResqmlUom__kcal_x005bth_x005d_x002fkg = 715, resqml2__ResqmlUom__kcal_x005bth_x005d_x002fm3 = 716, resqml2__ResqmlUom__kcal_x005bth_x005d_x002fmol = 717, resqml2__ResqmlUom__kcd = 718, resqml2__ResqmlUom__kdyne = 719, resqml2__ResqmlUom__kEuc = 720, resqml2__ResqmlUom__keV = 721, resqml2__ResqmlUom__kF = 722, resqml2__ResqmlUom__kg = 723, resqml2__ResqmlUom__kg_x002em = 724, resqml2__ResqmlUom__kg_x002em_x002fcm2 = 725, resqml2__ResqmlUom__kg_x002em_x002fs = 726, resqml2__ResqmlUom__kg_x002em2 = 727, resqml2__ResqmlUom__kg_x002f_x0028kW_x002eh_x0029 = 728, resqml2__ResqmlUom__kg_x002f_x0028m_x002es_x0029 = 729, resqml2__ResqmlUom__kg_x002f_x0028m2_x002es_x0029 = 730, resqml2__ResqmlUom__kg_x002fd = 731, resqml2__ResqmlUom__kg_x002fdm3 = 732, resqml2__ResqmlUom__kg_x002fdm4 = 733, resqml2__ResqmlUom__kg_x002fh = 734, resqml2__ResqmlUom__kg_x002fJ = 735, resqml2__ResqmlUom__kg_x002fkg = 736, resqml2__ResqmlUom__kg_x002fL = 737, resqml2__ResqmlUom__kg_x002fm = 738, resqml2__ResqmlUom__kg_x002fm2 = 739, resqml2__ResqmlUom__kg_x002fm3 = 740, resqml2__ResqmlUom__kg_x002fm4 = 741, resqml2__ResqmlUom__kg_x002fmin = 742, resqml2__ResqmlUom__kg_x002fMJ = 743, resqml2__ResqmlUom__kg_x002fmol = 744, resqml2__ResqmlUom__kg_x002fs = 745, resqml2__ResqmlUom__kg_x002fsack_x005b94lbm_x005d = 746, resqml2__ResqmlUom__kg_x002ft = 747, resqml2__ResqmlUom__kgauss = 748, resqml2__ResqmlUom__kgf = 749, resqml2__ResqmlUom__kgf_x002em = 750, resqml2__ResqmlUom__kgf_x002em_x002fcm2 = 751, resqml2__ResqmlUom__kgf_x002em_x002fm = 752, resqml2__ResqmlUom__kgf_x002em2 = 753, resqml2__ResqmlUom__kgf_x002es_x002fm2 = 754, resqml2__ResqmlUom__kgf_x002fcm = 755, resqml2__ResqmlUom__kgf_x002fcm2 = 756, resqml2__ResqmlUom__kgf_x002fkgf = 757, resqml2__ResqmlUom__kgf_x002fm2 = 758, resqml2__ResqmlUom__kgf_x002fmm2 = 759, resqml2__ResqmlUom__kGy = 760, resqml2__ResqmlUom__kH = 761, resqml2__ResqmlUom__kHz = 762, resqml2__ResqmlUom__Kibyte = 763, resqml2__ResqmlUom__kJ = 764, resqml2__ResqmlUom__kJ_x002em_x002f_x0028h_x002em2_x002eK_x0029 = 765, resqml2__ResqmlUom__kJ_x002f_x0028h_x002em2_x002eK_x0029 = 766, resqml2__ResqmlUom__kJ_x002f_x0028kg_x002eK_x0029 = 767, resqml2__ResqmlUom__kJ_x002f_x0028kmol_x002eK_x0029 = 768, resqml2__ResqmlUom__kJ_x002fdm3 = 769, resqml2__ResqmlUom__kJ_x002fkg = 770, resqml2__ResqmlUom__kJ_x002fkmol = 771, resqml2__ResqmlUom__kJ_x002fm3 = 772, resqml2__ResqmlUom__klbf = 773, resqml2__ResqmlUom__klbm = 774, resqml2__ResqmlUom__klbm_x002fin = 775, resqml2__ResqmlUom__klx = 776, resqml2__ResqmlUom__km = 777, resqml2__ResqmlUom__km_x002fcm = 778, resqml2__ResqmlUom__km_x002fdm3 = 779, resqml2__ResqmlUom__km_x002fh = 780, resqml2__ResqmlUom__km_x002fL = 781, resqml2__ResqmlUom__km_x002fs = 782, resqml2__ResqmlUom__km2 = 783, resqml2__ResqmlUom__km3 = 784, resqml2__ResqmlUom__kmol = 785, resqml2__ResqmlUom__kmol_x002fh = 786, resqml2__ResqmlUom__kmol_x002fm3 = 787, resqml2__ResqmlUom__kmol_x002fs = 788, resqml2__ResqmlUom__kN = 789, resqml2__ResqmlUom__kN_x002em = 790, resqml2__ResqmlUom__kN_x002em2 = 791, resqml2__ResqmlUom__kN_x002fm = 792, resqml2__ResqmlUom__kN_x002fm2 = 793, resqml2__ResqmlUom__knot = 794, resqml2__ResqmlUom__kohm = 795, resqml2__ResqmlUom__kohm_x002em = 796, resqml2__ResqmlUom__kP = 797, resqml2__ResqmlUom__kPa = 798, resqml2__ResqmlUom__kPa_x002es_x002fm = 799, resqml2__ResqmlUom__kPa_x002fh = 800, resqml2__ResqmlUom__kPa_x002fhm = 801, resqml2__ResqmlUom__kPa_x002fm = 802, resqml2__ResqmlUom__kPa_x002fmin = 803, resqml2__ResqmlUom__kPa2 = 804, resqml2__ResqmlUom__kPa2_x002fcP = 805, resqml2__ResqmlUom__kpsi = 806, resqml2__ResqmlUom__kpsi2 = 807, resqml2__ResqmlUom__krad = 808, resqml2__ResqmlUom__krd = 809, resqml2__ResqmlUom__kS = 810, resqml2__ResqmlUom__kS_x002fm = 811, resqml2__ResqmlUom__kT = 812, resqml2__ResqmlUom__kV = 813, resqml2__ResqmlUom__kW = 814, resqml2__ResqmlUom__kW_x002eh = 815, resqml2__ResqmlUom__kW_x002eh_x002f_x0028kg_x002edegC_x0029 = 816, resqml2__ResqmlUom__kW_x002eh_x002fdm3 = 817, resqml2__ResqmlUom__kW_x002eh_x002fkg = 818, resqml2__ResqmlUom__kW_x002eh_x002fm3 = 819, resqml2__ResqmlUom__kW_x002f_x0028m2_x002eK_x0029 = 820, resqml2__ResqmlUom__kW_x002f_x0028m3_x002eK_x0029 = 821, resqml2__ResqmlUom__kW_x002fcm2 = 822, resqml2__ResqmlUom__kW_x002fm2 = 823, resqml2__ResqmlUom__kW_x002fm3 = 824, resqml2__ResqmlUom__kWb = 825, resqml2__ResqmlUom__L = 826, resqml2__ResqmlUom__L_x002f_x0028bar_x002emin_x0029 = 827, resqml2__ResqmlUom__L_x002fh = 828, resqml2__ResqmlUom__L_x002fkg = 829, resqml2__ResqmlUom__L_x002fkmol = 830, resqml2__ResqmlUom__L_x002fm = 831, resqml2__ResqmlUom__L_x002fm3 = 832, resqml2__ResqmlUom__L_x002fmin = 833, resqml2__ResqmlUom__L_x002fmol = 834, resqml2__ResqmlUom__L_x002fs = 835, resqml2__ResqmlUom__L_x002fs2 = 836, resqml2__ResqmlUom__L_x002ft = 837, resqml2__ResqmlUom__L_x002fton_x005bUK_x005d = 838, resqml2__ResqmlUom__lbf = 839, resqml2__ResqmlUom__lbf_x002eft = 840, resqml2__ResqmlUom__lbf_x002eft_x002fbbl = 841, resqml2__ResqmlUom__lbf_x002eft_x002fgal_x005bUS_x005d = 842, resqml2__ResqmlUom__lbf_x002eft_x002fin = 843, resqml2__ResqmlUom__lbf_x002eft_x002fin2 = 844, resqml2__ResqmlUom__lbf_x002eft_x002flbm = 845, resqml2__ResqmlUom__lbf_x002eft_x002fmin = 846, resqml2__ResqmlUom__lbf_x002eft_x002fs = 847, resqml2__ResqmlUom__lbf_x002ein = 848, resqml2__ResqmlUom__lbf_x002ein_x002fin = 849, resqml2__ResqmlUom__lbf_x002ein2 = 850, resqml2__ResqmlUom__lbf_x002es_x002fft2 = 851, resqml2__ResqmlUom__lbf_x002es_x002fin2 = 852, resqml2__ResqmlUom__lbf_x002fft = 853, resqml2__ResqmlUom__lbf_x002fft2 = 854, resqml2__ResqmlUom__lbf_x002fft3 = 855, resqml2__ResqmlUom__lbf_x002fgal_x005bUS_x005d = 856, resqml2__ResqmlUom__lbf_x002fin = 857, resqml2__ResqmlUom__lbf_x002flbf = 858, resqml2__ResqmlUom__lbm = 859, resqml2__ResqmlUom__lbm_x002eft = 860, resqml2__ResqmlUom__lbm_x002eft_x002fs = 861, resqml2__ResqmlUom__lbm_x002eft2 = 862, resqml2__ResqmlUom__lbm_x002eft2_x002fs2 = 863, resqml2__ResqmlUom__lbm_x002f_x0028ft_x002eh_x0029 = 864, resqml2__ResqmlUom__lbm_x002f_x0028ft_x002es_x0029 = 865, resqml2__ResqmlUom__lbm_x002f_x0028ft2_x002eh_x0029 = 866, resqml2__ResqmlUom__lbm_x002f_x0028ft2_x002es_x0029 = 867, resqml2__ResqmlUom__lbm_x002f_x0028gal_x005bUK_x005d_x002eft_x0029 = 868, resqml2__ResqmlUom__lbm_x002f_x0028gal_x005bUS_x005d_x002eft_x0029 = 869, resqml2__ResqmlUom__lbm_x002f_x0028hp_x002eh_x0029 = 870, resqml2__ResqmlUom__lbm_x002fbbl = 871, resqml2__ResqmlUom__lbm_x002fd = 872, resqml2__ResqmlUom__lbm_x002fft = 873, resqml2__ResqmlUom__lbm_x002fft2 = 874, resqml2__ResqmlUom__lbm_x002fft3 = 875, resqml2__ResqmlUom__lbm_x002fft4 = 876, resqml2__ResqmlUom__lbm_x002fgal_x005bUK_x005d = 877, resqml2__ResqmlUom__lbm_x002fgal_x005bUS_x005d = 878, resqml2__ResqmlUom__lbm_x002fh = 879, resqml2__ResqmlUom__lbm_x002fin3 = 880, resqml2__ResqmlUom__lbm_x002flbmol = 881, resqml2__ResqmlUom__lbm_x002fmin = 882, resqml2__ResqmlUom__lbm_x002fs = 883, resqml2__ResqmlUom__lbmol = 884, resqml2__ResqmlUom__lbmol_x002f_x0028h_x002eft2_x0029 = 885, resqml2__ResqmlUom__lbmol_x002f_x0028s_x002eft2_x0029 = 886, resqml2__ResqmlUom__lbmol_x002fft3 = 887, resqml2__ResqmlUom__lbmol_x002fgal_x005bUK_x005d = 888, resqml2__ResqmlUom__lbmol_x002fgal_x005bUS_x005d = 889, resqml2__ResqmlUom__lbmol_x002fh = 890, resqml2__ResqmlUom__lbmol_x002fs = 891, resqml2__ResqmlUom__link = 892, resqml2__ResqmlUom__link_x005bBnA_x005d = 893, resqml2__ResqmlUom__link_x005bBnB_x005d = 894, resqml2__ResqmlUom__link_x005bCla_x005d = 895, resqml2__ResqmlUom__link_x005bSe_x005d = 896, resqml2__ResqmlUom__link_x005bSeT_x005d = 897, resqml2__ResqmlUom__link_x005bUS_x005d = 898, resqml2__ResqmlUom__lm = 899, resqml2__ResqmlUom__lm_x002es = 900, resqml2__ResqmlUom__lm_x002fm2 = 901, resqml2__ResqmlUom__lm_x002fW = 902, resqml2__ResqmlUom__lx = 903, resqml2__ResqmlUom__lx_x002es = 904, resqml2__ResqmlUom__m = 905, resqml2__ResqmlUom__m_x002f_x0028m_x002eK_x0029 = 906, resqml2__ResqmlUom__m_x002fcm = 907, resqml2__ResqmlUom__m_x002fd = 908, resqml2__ResqmlUom__m_x002fh = 909, resqml2__ResqmlUom__m_x002fK = 910, resqml2__ResqmlUom__m_x002fkg = 911, resqml2__ResqmlUom__m_x002fkm = 912, resqml2__ResqmlUom__m_x002fkPa = 913, resqml2__ResqmlUom__m_x002fm = 914, resqml2__ResqmlUom__m_x002fm3 = 915, resqml2__ResqmlUom__m_x002fmin = 916, resqml2__ResqmlUom__m_x002fms = 917, resqml2__ResqmlUom__m_x002fPa = 918, resqml2__ResqmlUom__m_x002fs = 919, resqml2__ResqmlUom__m_x002fs2 = 920, resqml2__ResqmlUom__m_x005bGer_x005d = 921, resqml2__ResqmlUom__m2 = 922, resqml2__ResqmlUom__m2_x002f_x0028kPa_x002ed_x0029 = 923, resqml2__ResqmlUom__m2_x002f_x0028Pa_x002es_x0029 = 924, resqml2__ResqmlUom__m2_x002fcm3 = 925, resqml2__ResqmlUom__m2_x002fd = 926, resqml2__ResqmlUom__m2_x002fg = 927, resqml2__ResqmlUom__m2_x002fh = 928, resqml2__ResqmlUom__m2_x002fkg = 929, resqml2__ResqmlUom__m2_x002fm2 = 930, resqml2__ResqmlUom__m2_x002fm3 = 931, resqml2__ResqmlUom__m2_x002fmol = 932, resqml2__ResqmlUom__m2_x002fs = 933, resqml2__ResqmlUom__m3 = 934, resqml2__ResqmlUom__m3_x002f_x0028bar_x002ed_x0029 = 935, resqml2__ResqmlUom__m3_x002f_x0028bar_x002eh_x0029 = 936, resqml2__ResqmlUom__m3_x002f_x0028bar_x002emin_x0029 = 937, resqml2__ResqmlUom__m3_x002f_x0028d_x002em_x0029 = 938, resqml2__ResqmlUom__m3_x002f_x0028h_x002em_x0029 = 939, resqml2__ResqmlUom__m3_x002f_x0028ha_x002em_x0029 = 940, resqml2__ResqmlUom__m3_x002f_x0028kPa_x002ed_x0029 = 941, resqml2__ResqmlUom__m3_x002f_x0028kPa_x002eh_x0029 = 942, resqml2__ResqmlUom__m3_x002f_x0028kW_x002eh_x0029 = 943, resqml2__ResqmlUom__m3_x002f_x0028m3_x002eK_x0029 = 944, resqml2__ResqmlUom__m3_x002f_x0028Pa_x002es_x0029 = 945, resqml2__ResqmlUom__m3_x002f_x0028psi_x002ed_x0029 = 946, resqml2__ResqmlUom__m3_x002f_x0028s_x002eft_x0029 = 947, resqml2__ResqmlUom__m3_x002f_x0028s_x002em_x0029 = 948, resqml2__ResqmlUom__m3_x002f_x0028s_x002em2_x0029 = 949, resqml2__ResqmlUom__m3_x002f_x0028s_x002em3_x0029 = 950, resqml2__ResqmlUom__m3_x002fbbl = 951, resqml2__ResqmlUom__m3_x002fd = 952, resqml2__ResqmlUom__m3_x002fd2 = 953, resqml2__ResqmlUom__m3_x002fg = 954, resqml2__ResqmlUom__m3_x002fh = 955, resqml2__ResqmlUom__m3_x002fJ = 956, resqml2__ResqmlUom__m3_x002fkg = 957, resqml2__ResqmlUom__m3_x002fkm = 958, resqml2__ResqmlUom__m3_x002fkmol = 959, resqml2__ResqmlUom__m3_x002fkPa = 960, resqml2__ResqmlUom__m3_x002fm = 961, resqml2__ResqmlUom__m3_x002fm2 = 962, resqml2__ResqmlUom__m3_x002fm3 = 963, resqml2__ResqmlUom__m3_x002fmin = 964, resqml2__ResqmlUom__m3_x002fmol = 965, resqml2__ResqmlUom__m3_x002fPa = 966, resqml2__ResqmlUom__m3_x002frad = 967, resqml2__ResqmlUom__m3_x002frev = 968, resqml2__ResqmlUom__m3_x002fs = 969, resqml2__ResqmlUom__m3_x002fs2 = 970, resqml2__ResqmlUom__m3_x002ft = 971, resqml2__ResqmlUom__m3_x002fton_x005bUK_x005d = 972, resqml2__ResqmlUom__m3_x002fton_x005bUS_x005d = 973, resqml2__ResqmlUom__m4 = 974, resqml2__ResqmlUom__m4_x002fs = 975, resqml2__ResqmlUom__MA = 976, resqml2__ResqmlUom__mA = 977, resqml2__ResqmlUom__mA_x002fcm2 = 978, resqml2__ResqmlUom__mA_x002fft2 = 979, resqml2__ResqmlUom__Ma_x005bt_x005d = 980, resqml2__ResqmlUom__mbar = 981, resqml2__ResqmlUom__MBq = 982, resqml2__ResqmlUom__mC = 983, resqml2__ResqmlUom__MC = 984, resqml2__ResqmlUom__mC_x002fm2 = 985, resqml2__ResqmlUom__mcal_x005bth_x005d = 986, resqml2__ResqmlUom__Mcal_x005bth_x005d = 987, resqml2__ResqmlUom__mCi = 988, resqml2__ResqmlUom__mD = 989, resqml2__ResqmlUom__mD_x002eft = 990, resqml2__ResqmlUom__mD_x002eft2_x002f_x0028lbf_x002es_x0029 = 991, resqml2__ResqmlUom__mD_x002ein2_x002f_x0028lbf_x002es_x0029 = 992, resqml2__ResqmlUom__mD_x002em = 993, resqml2__ResqmlUom__mD_x002f_x0028Pa_x002es_x0029 = 994, resqml2__ResqmlUom__mD_x002fcP = 995, resqml2__ResqmlUom__MEuc = 996, resqml2__ResqmlUom__mEuc = 997, resqml2__ResqmlUom__meV = 998, resqml2__ResqmlUom__MeV = 999, resqml2__ResqmlUom__MF = 1000, resqml2__ResqmlUom__mF = 1001, resqml2__ResqmlUom__Mg = 1002, resqml2__ResqmlUom__mg = 1003, resqml2__ResqmlUom__Mg_x002fa = 1004, resqml2__ResqmlUom__Mg_x002fd = 1005, resqml2__ResqmlUom__mg_x002fdm3 = 1006, resqml2__ResqmlUom__mg_x002fg = 1007, resqml2__ResqmlUom__mg_x002fgal_x005bUS_x005d = 1008, resqml2__ResqmlUom__Mg_x002fh = 1009, resqml2__ResqmlUom__Mg_x002fin = 1010, resqml2__ResqmlUom__mg_x002fJ = 1011, resqml2__ResqmlUom__mg_x002fkg = 1012, resqml2__ResqmlUom__mg_x002fL = 1013, resqml2__ResqmlUom__Mg_x002fm2 = 1014, resqml2__ResqmlUom__mg_x002fm3 = 1015, resqml2__ResqmlUom__Mg_x002fm3 = 1016, resqml2__ResqmlUom__Mg_x002fmin = 1017, resqml2__ResqmlUom__mGal = 1018, resqml2__ResqmlUom__mgauss = 1019, resqml2__ResqmlUom__Mgauss = 1020, resqml2__ResqmlUom__Mgf = 1021, resqml2__ResqmlUom__mgn = 1022, resqml2__ResqmlUom__mGy = 1023, resqml2__ResqmlUom__MGy = 1024, resqml2__ResqmlUom__mH = 1025, resqml2__ResqmlUom__MH = 1026, resqml2__ResqmlUom__mHz = 1027, resqml2__ResqmlUom__MHz = 1028, resqml2__ResqmlUom__mi = 1029, resqml2__ResqmlUom__mi_x002fgal_x005bUK_x005d = 1030, resqml2__ResqmlUom__mi_x002fgal_x005bUS_x005d = 1031, resqml2__ResqmlUom__mi_x002fh = 1032, resqml2__ResqmlUom__mi_x002fin = 1033, resqml2__ResqmlUom__mi_x005bnaut_x005d = 1034, resqml2__ResqmlUom__mi_x005bnautUK_x005d = 1035, resqml2__ResqmlUom__mi_x005bUS_x005d = 1036, resqml2__ResqmlUom__mi_x005bUS_x005d2 = 1037, resqml2__ResqmlUom__mi2 = 1038, resqml2__ResqmlUom__mi3 = 1039, resqml2__ResqmlUom__Mibyte = 1040, resqml2__ResqmlUom__mil = 1041, resqml2__ResqmlUom__mil_x002fa = 1042, resqml2__ResqmlUom__mila = 1043, resqml2__ResqmlUom__min_ = 1044, resqml2__ResqmlUom__min_x002fft = 1045, resqml2__ResqmlUom__min_x002fm = 1046, resqml2__ResqmlUom__mina = 1047, resqml2__ResqmlUom__MJ = 1048, resqml2__ResqmlUom__mJ = 1049, resqml2__ResqmlUom__MJ_x002fa = 1050, resqml2__ResqmlUom__mJ_x002fcm2 = 1051, resqml2__ResqmlUom__MJ_x002fkg = 1052, resqml2__ResqmlUom__MJ_x002fkmol = 1053, resqml2__ResqmlUom__MJ_x002fm = 1054, resqml2__ResqmlUom__mJ_x002fm2 = 1055, resqml2__ResqmlUom__MJ_x002fm3 = 1056, resqml2__ResqmlUom__mL = 1057, resqml2__ResqmlUom__mL_x002fgal_x005bUK_x005d = 1058, resqml2__ResqmlUom__mL_x002fgal_x005bUS_x005d = 1059, resqml2__ResqmlUom__mL_x002fmL = 1060, resqml2__ResqmlUom__Mm = 1061, resqml2__ResqmlUom__mm = 1062, resqml2__ResqmlUom__mm_x002f_x0028mm_x002eK_x0029 = 1063, resqml2__ResqmlUom__mm_x002fa = 1064, resqml2__ResqmlUom__mm_x002fs = 1065, resqml2__ResqmlUom__mm2 = 1066, resqml2__ResqmlUom__mm2_x002fmm2 = 1067, resqml2__ResqmlUom__mm2_x002fs = 1068, resqml2__ResqmlUom__mm3 = 1069, resqml2__ResqmlUom__mm3_x002fJ = 1070, resqml2__ResqmlUom__mmHg_x005b0degC_x005d = 1071, resqml2__ResqmlUom__mmol = 1072, resqml2__ResqmlUom__mN = 1073, resqml2__ResqmlUom__MN = 1074, resqml2__ResqmlUom__mN_x002em2 = 1075, resqml2__ResqmlUom__mN_x002fkm = 1076, resqml2__ResqmlUom__mN_x002fm = 1077, resqml2__ResqmlUom__Mohm = 1078, resqml2__ResqmlUom__mohm = 1079, resqml2__ResqmlUom__mol = 1080, resqml2__ResqmlUom__mol_x002em2_x002f_x0028mol_x002es_x0029 = 1081, resqml2__ResqmlUom__mol_x002f_x0028s_x002em2_x0029 = 1082, resqml2__ResqmlUom__mol_x002fm2 = 1083, resqml2__ResqmlUom__mol_x002fm3 = 1084, resqml2__ResqmlUom__mol_x002fmol = 1085, resqml2__ResqmlUom__mol_x002fs = 1086, resqml2__ResqmlUom__mP = 1087, resqml2__ResqmlUom__MP = 1088, resqml2__ResqmlUom__mPa = 1089, resqml2__ResqmlUom__MPa = 1090, resqml2__ResqmlUom__mPa_x002es = 1091, resqml2__ResqmlUom__MPa_x002es_x002fm = 1092, resqml2__ResqmlUom__MPa_x002fh = 1093, resqml2__ResqmlUom__MPa_x002fm = 1094, resqml2__ResqmlUom__Mpsi = 1095, resqml2__ResqmlUom__Mrad = 1096, resqml2__ResqmlUom__mrad = 1097, resqml2__ResqmlUom__Mrd = 1098, resqml2__ResqmlUom__mrd = 1099, resqml2__ResqmlUom__mrem = 1100, resqml2__ResqmlUom__mrem_x002fh = 1101, resqml2__ResqmlUom__MS = 1102, resqml2__ResqmlUom__ms = 1103, resqml2__ResqmlUom__mS = 1104, resqml2__ResqmlUom__ms_x002fcm = 1105, resqml2__ResqmlUom__mS_x002fcm = 1106, resqml2__ResqmlUom__ms_x002fft = 1107, resqml2__ResqmlUom__ms_x002fin = 1108, resqml2__ResqmlUom__mS_x002fm = 1109, resqml2__ResqmlUom__ms_x002fm = 1110, resqml2__ResqmlUom__ms_x002fs = 1111, resqml2__ResqmlUom__mSv = 1112, resqml2__ResqmlUom__mSv_x002fh = 1113, resqml2__ResqmlUom__mT = 1114, resqml2__ResqmlUom__mT_x002fdm = 1115, resqml2__ResqmlUom__MV = 1116, resqml2__ResqmlUom__mV = 1117, resqml2__ResqmlUom__mV_x002fft = 1118, resqml2__ResqmlUom__mV_x002fm = 1119, resqml2__ResqmlUom__MW = 1120, resqml2__ResqmlUom__mW = 1121, resqml2__ResqmlUom__MW_x002eh = 1122, resqml2__ResqmlUom__MW_x002eh_x002fkg = 1123, resqml2__ResqmlUom__MW_x002eh_x002fm3 = 1124, resqml2__ResqmlUom__mW_x002fm2 = 1125, resqml2__ResqmlUom__MWb = 1126, resqml2__ResqmlUom__mWb = 1127, resqml2__ResqmlUom__N = 1128, resqml2__ResqmlUom__N_x002em = 1129, resqml2__ResqmlUom__N_x002em_x002fm = 1130, resqml2__ResqmlUom__N_x002em2 = 1131, resqml2__ResqmlUom__N_x002es_x002fm2 = 1132, resqml2__ResqmlUom__N_x002fm = 1133, resqml2__ResqmlUom__N_x002fm2 = 1134, resqml2__ResqmlUom__N_x002fm3 = 1135, resqml2__ResqmlUom__N_x002fmm2 = 1136, resqml2__ResqmlUom__N_x002fN = 1137, resqml2__ResqmlUom__na = 1138, resqml2__ResqmlUom__nA = 1139, resqml2__ResqmlUom__nAPI = 1140, resqml2__ResqmlUom__nC = 1141, resqml2__ResqmlUom__ncal_x005bth_x005d = 1142, resqml2__ResqmlUom__nCi = 1143, resqml2__ResqmlUom__nEuc = 1144, resqml2__ResqmlUom__neV = 1145, resqml2__ResqmlUom__nF = 1146, resqml2__ResqmlUom__ng = 1147, resqml2__ResqmlUom__ng_x002fg = 1148, resqml2__ResqmlUom__ng_x002fmg = 1149, resqml2__ResqmlUom__ngauss = 1150, resqml2__ResqmlUom__nGy = 1151, resqml2__ResqmlUom__nH = 1152, resqml2__ResqmlUom__nHz = 1153, resqml2__ResqmlUom__nJ = 1154, resqml2__ResqmlUom__nm = 1155, resqml2__ResqmlUom__nm_x002fs = 1156, resqml2__ResqmlUom__nN = 1157, resqml2__ResqmlUom__nohm = 1158, resqml2__ResqmlUom__nohm_x002emil2_x002fft = 1159, resqml2__ResqmlUom__nohm_x002emm2_x002fm = 1160, resqml2__ResqmlUom__nP = 1161, resqml2__ResqmlUom__nPa = 1162, resqml2__ResqmlUom__nrd = 1163, resqml2__ResqmlUom__ns = 1164, resqml2__ResqmlUom__nS = 1165, resqml2__ResqmlUom__ns_x002fft = 1166, resqml2__ResqmlUom__ns_x002fm = 1167, resqml2__ResqmlUom__nT = 1168, resqml2__ResqmlUom__nV = 1169, resqml2__ResqmlUom__nW = 1170, resqml2__ResqmlUom__nWb = 1171, resqml2__ResqmlUom__O = 1172, resqml2__ResqmlUom__Oe = 1173, resqml2__ResqmlUom__ohm = 1174, resqml2__ResqmlUom__ohm_x002ecm = 1175, resqml2__ResqmlUom__ohm_x002em = 1176, resqml2__ResqmlUom__ohm_x002em2_x002fm = 1177, resqml2__ResqmlUom__ohm_x002fm = 1178, resqml2__ResqmlUom__ozf = 1179, resqml2__ResqmlUom__ozm = 1180, resqml2__ResqmlUom__ozm_x005btroy_x005d = 1181, resqml2__ResqmlUom__P = 1182, resqml2__ResqmlUom__Pa = 1183, resqml2__ResqmlUom__pA = 1184, resqml2__ResqmlUom__Pa_x002es = 1185, resqml2__ResqmlUom__Pa_x002es_x002em3_x002fkg = 1186, resqml2__ResqmlUom__Pa_x002es_x002fm3 = 1187, resqml2__ResqmlUom__Pa_x002es2_x002fm3 = 1188, resqml2__ResqmlUom__Pa_x002fh = 1189, resqml2__ResqmlUom__Pa_x002fm = 1190, resqml2__ResqmlUom__Pa_x002fm3 = 1191, resqml2__ResqmlUom__Pa_x002fs = 1192, resqml2__ResqmlUom__Pa2 = 1193, resqml2__ResqmlUom__Pa2_x002f_x0028Pa_x002es_x0029 = 1194, resqml2__ResqmlUom__pC = 1195, resqml2__ResqmlUom__pcal_x005bth_x005d = 1196, resqml2__ResqmlUom__pCi = 1197, resqml2__ResqmlUom__pCi_x002fg = 1198, resqml2__ResqmlUom__pdl = 1199, resqml2__ResqmlUom__pdl_x002ecm2 = 1200, resqml2__ResqmlUom__pdl_x002eft = 1201, resqml2__ResqmlUom__pdl_x002fcm = 1202, resqml2__ResqmlUom__pEuc = 1203, resqml2__ResqmlUom__peV = 1204, resqml2__ResqmlUom__pF = 1205, resqml2__ResqmlUom__pg = 1206, resqml2__ResqmlUom__pgauss = 1207, resqml2__ResqmlUom__pGy = 1208, resqml2__ResqmlUom__pHz = 1209, resqml2__ResqmlUom__pJ = 1210, resqml2__ResqmlUom__pm = 1211, resqml2__ResqmlUom__pN = 1212, resqml2__ResqmlUom__pohm = 1213, resqml2__ResqmlUom__pP = 1214, resqml2__ResqmlUom__pPa = 1215, resqml2__ResqmlUom__ppk = 1216, resqml2__ResqmlUom__ppm = 1217, resqml2__ResqmlUom__ppm_x005bmass_x005d = 1218, resqml2__ResqmlUom__ppm_x005bvol_x005d = 1219, resqml2__ResqmlUom__ppm_x005bvol_x005d_x002fdegC = 1220, resqml2__ResqmlUom__ppm_x005bvol_x005d_x002fdegF = 1221, resqml2__ResqmlUom__prd = 1222, resqml2__ResqmlUom__ps = 1223, resqml2__ResqmlUom__pS = 1224, resqml2__ResqmlUom__psi = 1225, resqml2__ResqmlUom__psi_x002ed_x002fbbl = 1226, resqml2__ResqmlUom__psi_x002es = 1227, resqml2__ResqmlUom__psi_x002fft = 1228, resqml2__ResqmlUom__psi_x002fh = 1229, resqml2__ResqmlUom__psi_x002fm = 1230, resqml2__ResqmlUom__psi_x002fmin = 1231, resqml2__ResqmlUom__psi2 = 1232, resqml2__ResqmlUom__psi2_x002ed_x002f_x0028cP_x002eft3_x0029 = 1233, resqml2__ResqmlUom__psi2_x002fcP = 1234, resqml2__ResqmlUom__pT = 1235, resqml2__ResqmlUom__pt_x005bUK_x005d = 1236, resqml2__ResqmlUom__pt_x005bUK_x005d_x002f_x0028hp_x002eh_x0029 = 1237, resqml2__ResqmlUom__pt_x005bUS_x005d = 1238, resqml2__ResqmlUom__pV = 1239, resqml2__ResqmlUom__pW = 1240, resqml2__ResqmlUom__pWb = 1241, resqml2__ResqmlUom__qt_x005bUK_x005d = 1242, resqml2__ResqmlUom__qt_x005bUS_x005d = 1243, resqml2__ResqmlUom__quad = 1244, resqml2__ResqmlUom__quad_x002fa = 1245, resqml2__ResqmlUom__rad = 1246, resqml2__ResqmlUom__rad_x002fft = 1247, resqml2__ResqmlUom__rad_x002fft3 = 1248, resqml2__ResqmlUom__rad_x002fm = 1249, resqml2__ResqmlUom__rad_x002fm3 = 1250, resqml2__ResqmlUom__rad_x002fs = 1251, resqml2__ResqmlUom__rad_x002fs2 = 1252, resqml2__ResqmlUom__rd = 1253, resqml2__ResqmlUom__rem = 1254, resqml2__ResqmlUom__rem_x002fh = 1255, resqml2__ResqmlUom__rev = 1256, resqml2__ResqmlUom__rev_x002fft = 1257, resqml2__ResqmlUom__rev_x002fm = 1258, resqml2__ResqmlUom__rev_x002fs = 1259, resqml2__ResqmlUom__rod_x005bUS_x005d = 1260, resqml2__ResqmlUom__rpm = 1261, resqml2__ResqmlUom__rpm_x002fs = 1262, resqml2__ResqmlUom__s = 1263, resqml2__ResqmlUom__S = 1264, resqml2__ResqmlUom__s_x002fcm = 1265, resqml2__ResqmlUom__s_x002fft = 1266, resqml2__ResqmlUom__s_x002fft3 = 1267, resqml2__ResqmlUom__s_x002fin = 1268, resqml2__ResqmlUom__s_x002fkg = 1269, resqml2__ResqmlUom__s_x002fL = 1270, resqml2__ResqmlUom__s_x002fm = 1271, resqml2__ResqmlUom__S_x002fm = 1272, resqml2__ResqmlUom__s_x002fm3 = 1273, resqml2__ResqmlUom__s_x002fqt_x005bUK_x005d = 1274, resqml2__ResqmlUom__s_x002fqt_x005bUS_x005d = 1275, resqml2__ResqmlUom__s_x002fs = 1276, resqml2__ResqmlUom__sack_x005b94lbm_x005d = 1277, resqml2__ResqmlUom__seca = 1278, resqml2__ResqmlUom__section = 1279, resqml2__ResqmlUom__sr = 1280, resqml2__ResqmlUom__St = 1281, resqml2__ResqmlUom__Sv = 1282, resqml2__ResqmlUom__Sv_x002fh = 1283, resqml2__ResqmlUom__Sv_x002fs = 1284, resqml2__ResqmlUom__t = 1285, resqml2__ResqmlUom__T = 1286, resqml2__ResqmlUom__t_x002fa = 1287, resqml2__ResqmlUom__t_x002fd = 1288, resqml2__ResqmlUom__t_x002fh = 1289, resqml2__ResqmlUom__T_x002fm = 1290, resqml2__ResqmlUom__t_x002fm3 = 1291, resqml2__ResqmlUom__t_x002fmin = 1292, resqml2__ResqmlUom__TA = 1293, resqml2__ResqmlUom__Ta_x005bt_x005d = 1294, resqml2__ResqmlUom__TBq = 1295, resqml2__ResqmlUom__TC = 1296, resqml2__ResqmlUom__Tcal_x005bth_x005d = 1297, resqml2__ResqmlUom__TD_x005bAPI_x005d = 1298, resqml2__ResqmlUom__TD_x005bAPI_x005d_x002em = 1299, resqml2__ResqmlUom__TD_x005bAPI_x005d_x002f_x0028Pa_x002es_x0029 = 1300, resqml2__ResqmlUom__TEuc = 1301, resqml2__ResqmlUom__TeV = 1302, resqml2__ResqmlUom__TF = 1303, resqml2__ResqmlUom__Tg = 1304, resqml2__ResqmlUom__Tgauss = 1305, resqml2__ResqmlUom__TGy = 1306, resqml2__ResqmlUom__TH = 1307, resqml2__ResqmlUom__therm_x005bEC_x005d = 1308, resqml2__ResqmlUom__therm_x005bUK_x005d = 1309, resqml2__ResqmlUom__therm_x005bUS_x005d = 1310, resqml2__ResqmlUom__THz = 1311, resqml2__ResqmlUom__TJ = 1312, resqml2__ResqmlUom__TJ_x002fa = 1313, resqml2__ResqmlUom__Tm = 1314, resqml2__ResqmlUom__TN = 1315, resqml2__ResqmlUom__Tohm = 1316, resqml2__ResqmlUom__ton_x005bUK_x005d = 1317, resqml2__ResqmlUom__ton_x005bUK_x005d_x002fa = 1318, resqml2__ResqmlUom__ton_x005bUK_x005d_x002fd = 1319, resqml2__ResqmlUom__ton_x005bUK_x005d_x002fh = 1320, resqml2__ResqmlUom__ton_x005bUK_x005d_x002fmin = 1321, resqml2__ResqmlUom__ton_x005bUS_x005d = 1322, resqml2__ResqmlUom__ton_x005bUS_x005d_x002fa = 1323, resqml2__ResqmlUom__ton_x005bUS_x005d_x002fd = 1324, resqml2__ResqmlUom__ton_x005bUS_x005d_x002fft2 = 1325, resqml2__ResqmlUom__ton_x005bUS_x005d_x002fh = 1326, resqml2__ResqmlUom__ton_x005bUS_x005d_x002fmin = 1327, resqml2__ResqmlUom__tonf_x005bUK_x005d = 1328, resqml2__ResqmlUom__tonf_x005bUK_x005d_x002eft2 = 1329, resqml2__ResqmlUom__tonf_x005bUK_x005d_x002fft = 1330, resqml2__ResqmlUom__tonf_x005bUK_x005d_x002fft2 = 1331, resqml2__ResqmlUom__tonf_x005bUS_x005d = 1332, resqml2__ResqmlUom__tonf_x005bUS_x005d_x002eft = 1333, resqml2__ResqmlUom__tonf_x005bUS_x005d_x002eft2 = 1334, resqml2__ResqmlUom__tonf_x005bUS_x005d_x002emi = 1335, resqml2__ResqmlUom__tonf_x005bUS_x005d_x002emi_x002fbbl = 1336, resqml2__ResqmlUom__tonf_x005bUS_x005d_x002emi_x002fft = 1337, resqml2__ResqmlUom__tonf_x005bUS_x005d_x002fft = 1338, resqml2__ResqmlUom__tonf_x005bUS_x005d_x002fft2 = 1339, resqml2__ResqmlUom__tonf_x005bUS_x005d_x002fin2 = 1340, resqml2__ResqmlUom__tonRefrig = 1341, resqml2__ResqmlUom__torr = 1342, resqml2__ResqmlUom__TP = 1343, resqml2__ResqmlUom__TPa = 1344, resqml2__ResqmlUom__Trd = 1345, resqml2__ResqmlUom__TS = 1346, resqml2__ResqmlUom__TT = 1347, resqml2__ResqmlUom__TV = 1348, resqml2__ResqmlUom__TW = 1349, resqml2__ResqmlUom__TW_x002eh = 1350, resqml2__ResqmlUom__TWb = 1351, resqml2__ResqmlUom__uA = 1352, resqml2__ResqmlUom__uA_x002fcm2 = 1353, resqml2__ResqmlUom__uA_x002fin2 = 1354, resqml2__ResqmlUom__ubar = 1355, resqml2__ResqmlUom__uC = 1356, resqml2__ResqmlUom__ucal_x005bth_x005d = 1357, resqml2__ResqmlUom__ucal_x005bth_x005d_x002f_x0028s_x002ecm2_x0029 = 1358, resqml2__ResqmlUom__ucal_x005bth_x005d_x002fs = 1359, resqml2__ResqmlUom__uCi = 1360, resqml2__ResqmlUom__uEuc = 1361, resqml2__ResqmlUom__ueV = 1362, resqml2__ResqmlUom__uF = 1363, resqml2__ResqmlUom__uF_x002fm = 1364, resqml2__ResqmlUom__ug = 1365, resqml2__ResqmlUom__ug_x002fcm3 = 1366, resqml2__ResqmlUom__ug_x002fg = 1367, resqml2__ResqmlUom__ug_x002fmg = 1368, resqml2__ResqmlUom__ugauss = 1369, resqml2__ResqmlUom__uGy = 1370, resqml2__ResqmlUom__uH = 1371, resqml2__ResqmlUom__uH_x002fm = 1372, resqml2__ResqmlUom__uHz = 1373, resqml2__ResqmlUom__uJ = 1374, resqml2__ResqmlUom__um = 1375, resqml2__ResqmlUom__um_x002fs = 1376, resqml2__ResqmlUom__um2 = 1377, resqml2__ResqmlUom__um2_x002em = 1378, resqml2__ResqmlUom__umHg_x005b0degC_x005d = 1379, resqml2__ResqmlUom__umol = 1380, resqml2__ResqmlUom__uN = 1381, resqml2__ResqmlUom__uohm = 1382, resqml2__ResqmlUom__uohm_x002fft = 1383, resqml2__ResqmlUom__uohm_x002fm = 1384, resqml2__ResqmlUom__uP = 1385, resqml2__ResqmlUom__uPa = 1386, resqml2__ResqmlUom__upsi = 1387, resqml2__ResqmlUom__urad = 1388, resqml2__ResqmlUom__urd = 1389, resqml2__ResqmlUom__uS = 1390, resqml2__ResqmlUom__us = 1391, resqml2__ResqmlUom__us_x002fft = 1392, resqml2__ResqmlUom__us_x002fin = 1393, resqml2__ResqmlUom__us_x002fm = 1394, resqml2__ResqmlUom__uT = 1395, resqml2__ResqmlUom__uV = 1396, resqml2__ResqmlUom__uV_x002fft = 1397, resqml2__ResqmlUom__uV_x002fm = 1398, resqml2__ResqmlUom__uW = 1399, resqml2__ResqmlUom__uW_x002fm3 = 1400, resqml2__ResqmlUom__uWb = 1401, resqml2__ResqmlUom__V = 1402, resqml2__ResqmlUom__V_x002fB = 1403, resqml2__ResqmlUom__V_x002fdB = 1404, resqml2__ResqmlUom__V_x002fm = 1405, resqml2__ResqmlUom__W = 1406, resqml2__ResqmlUom__W_x002em2_x002eK_x002f_x0028J_x002eK_x0029 = 1407, resqml2__ResqmlUom__W_x002f_x0028m_x002eK_x0029 = 1408, resqml2__ResqmlUom__W_x002f_x0028m2_x002eK_x0029 = 1409, resqml2__ResqmlUom__W_x002f_x0028m2_x002esr_x0029 = 1410, resqml2__ResqmlUom__W_x002f_x0028m3_x002eK_x0029 = 1411, resqml2__ResqmlUom__W_x002fcm2 = 1412, resqml2__ResqmlUom__W_x002fK = 1413, resqml2__ResqmlUom__W_x002fkW = 1414, resqml2__ResqmlUom__W_x002fm2 = 1415, resqml2__ResqmlUom__W_x002fm3 = 1416, resqml2__ResqmlUom__W_x002fmm2 = 1417, resqml2__ResqmlUom__W_x002fsr = 1418, resqml2__ResqmlUom__W_x002fW = 1419, resqml2__ResqmlUom__Wb = 1420, resqml2__ResqmlUom__Wb_x002em = 1421, resqml2__ResqmlUom__Wb_x002fm = 1422, resqml2__ResqmlUom__Wb_x002fmm = 1423, resqml2__ResqmlUom__wk = 1424, resqml2__ResqmlUom__yd = 1425, resqml2__ResqmlUom__yd_x005bBnA_x005d = 1426, resqml2__ResqmlUom__yd_x005bBnB_x005d = 1427, resqml2__ResqmlUom__yd_x005bCla_x005d = 1428, resqml2__ResqmlUom__yd_x005bInd_x005d = 1429, resqml2__ResqmlUom__yd_x005bInd37_x005d = 1430, resqml2__ResqmlUom__yd_x005bInd62_x005d = 1431, resqml2__ResqmlUom__yd_x005bInd75_x005d = 1432, resqml2__ResqmlUom__yd_x005bSe_x005d = 1433, resqml2__ResqmlUom__yd_x005bSeT_x005d = 1434, resqml2__ResqmlUom__yd_x005bUS_x005d = 1435, resqml2__ResqmlUom__yd2 = 1436, resqml2__ResqmlUom__yd3 = 1437 };
	enum resqml2__ResqmlPropertyKind { resqml2__ResqmlPropertyKind__absorbed_x0020dose = 0, resqml2__ResqmlPropertyKind__acceleration_x0020linear = 1, resqml2__ResqmlPropertyKind__activity_x0020_x0028of_x0020radioactivity_x0029 = 2, resqml2__ResqmlPropertyKind__amount_x0020of_x0020substance = 3, resqml2__ResqmlPropertyKind__amplitude = 4, resqml2__ResqmlPropertyKind__angle_x0020per_x0020length = 5, resqml2__ResqmlPropertyKind__angle_x0020per_x0020time = 6, resqml2__ResqmlPropertyKind__angle_x0020per_x0020volume = 7, resqml2__ResqmlPropertyKind__angular_x0020acceleration = 8, resqml2__ResqmlPropertyKind__area = 9, resqml2__ResqmlPropertyKind__area_x0020per_x0020area = 10, resqml2__ResqmlPropertyKind__area_x0020per_x0020volume = 11, resqml2__ResqmlPropertyKind__attenuation = 12, resqml2__ResqmlPropertyKind__attenuation_x0020per_x0020length = 13, resqml2__ResqmlPropertyKind__azimuth = 14, resqml2__ResqmlPropertyKind__bubble_x0020point_x0020pressure = 15, resqml2__ResqmlPropertyKind__bulk_x0020modulus = 16, resqml2__ResqmlPropertyKind__capacitance = 17, resqml2__ResqmlPropertyKind__categorical = 18, resqml2__ResqmlPropertyKind__cell_x0020length = 19, resqml2__ResqmlPropertyKind__charge_x0020density = 20, resqml2__ResqmlPropertyKind__chemical_x0020potential = 21, resqml2__ResqmlPropertyKind__code = 22, resqml2__ResqmlPropertyKind__compressibility = 23, resqml2__ResqmlPropertyKind__concentration_x0020of_x0020B = 24, resqml2__ResqmlPropertyKind__conductivity = 25, resqml2__ResqmlPropertyKind__continuous = 26, resqml2__ResqmlPropertyKind__cross_x0020section_x0020absorption = 27, resqml2__ResqmlPropertyKind__current_x0020density = 28, resqml2__ResqmlPropertyKind__Darcy_x0020flow_x0020coefficient = 29, resqml2__ResqmlPropertyKind__data_x0020transmission_x0020speed = 30, resqml2__ResqmlPropertyKind__delta_x0020temperature = 31, resqml2__ResqmlPropertyKind__density = 32, resqml2__ResqmlPropertyKind__depth = 33, resqml2__ResqmlPropertyKind__diffusion_x0020coefficient = 34, resqml2__ResqmlPropertyKind__digital_x0020storage = 35, resqml2__ResqmlPropertyKind__dimensionless = 36, resqml2__ResqmlPropertyKind__dip = 37, resqml2__ResqmlPropertyKind__discrete = 38, resqml2__ResqmlPropertyKind__dose_x0020equivalent = 39, resqml2__ResqmlPropertyKind__dose_x0020equivalent_x0020rate = 40, resqml2__ResqmlPropertyKind__dynamic_x0020viscosity = 41, resqml2__ResqmlPropertyKind__electric_x0020charge = 42, resqml2__ResqmlPropertyKind__electric_x0020conductance = 43, resqml2__ResqmlPropertyKind__electric_x0020current = 44, resqml2__ResqmlPropertyKind__electric_x0020dipole_x0020moment = 45, resqml2__ResqmlPropertyKind__electric_x0020field_x0020strength = 46, resqml2__ResqmlPropertyKind__electric_x0020polarization = 47, resqml2__ResqmlPropertyKind__electric_x0020potential = 48, resqml2__ResqmlPropertyKind__electrical_x0020resistivity = 49, resqml2__ResqmlPropertyKind__electrochemical_x0020equivalent = 50, resqml2__ResqmlPropertyKind__electromagnetic_x0020moment = 51, resqml2__ResqmlPropertyKind__energy_x0020length_x0020per_x0020area = 52, resqml2__ResqmlPropertyKind__energy_x0020length_x0020per_x0020time_x0020area_x0020temperature = 53, resqml2__ResqmlPropertyKind__energy_x0020per_x0020area = 54, resqml2__ResqmlPropertyKind__energy_x0020per_x0020length = 55, resqml2__ResqmlPropertyKind__equivalent_x0020per_x0020mass = 56, resqml2__ResqmlPropertyKind__equivalent_x0020per_x0020volume = 57, resqml2__ResqmlPropertyKind__exposure_x0020_x0028radioactivity_x0029 = 58, resqml2__ResqmlPropertyKind__fluid_x0020volume = 59, resqml2__ResqmlPropertyKind__force = 60, resqml2__ResqmlPropertyKind__force_x0020area = 61, resqml2__ResqmlPropertyKind__force_x0020length_x0020per_x0020length = 62, resqml2__ResqmlPropertyKind__force_x0020per_x0020force = 63, resqml2__ResqmlPropertyKind__force_x0020per_x0020length = 64, resqml2__ResqmlPropertyKind__force_x0020per_x0020volume = 65, resqml2__ResqmlPropertyKind__formation_x0020volume_x0020factor = 66, resqml2__ResqmlPropertyKind__frequency = 67, resqml2__ResqmlPropertyKind__frequency_x0020interval = 68, resqml2__ResqmlPropertyKind__gamma_x0020ray_x0020API_x0020unit = 69, resqml2__ResqmlPropertyKind__heat_x0020capacity = 70, resqml2__ResqmlPropertyKind__heat_x0020flow_x0020rate = 71, resqml2__ResqmlPropertyKind__heat_x0020transfer_x0020coefficient = 72, resqml2__ResqmlPropertyKind__illuminance = 73, resqml2__ResqmlPropertyKind__index = 74, resqml2__ResqmlPropertyKind__irradiance = 75, resqml2__ResqmlPropertyKind__isothermal_x0020compressibility = 76, resqml2__ResqmlPropertyKind__kinematic_x0020viscosity = 77, resqml2__ResqmlPropertyKind__Lambda_x0020Rho = 78, resqml2__ResqmlPropertyKind__Lame_x0020constant = 79, resqml2__ResqmlPropertyKind__length = 80, resqml2__ResqmlPropertyKind__length_x0020per_x0020length = 81, resqml2__ResqmlPropertyKind__length_x0020per_x0020temperature = 82, resqml2__ResqmlPropertyKind__length_x0020per_x0020volume = 83, resqml2__ResqmlPropertyKind__level_x0020of_x0020power_x0020intensity = 84, resqml2__ResqmlPropertyKind__light_x0020exposure = 85, resqml2__ResqmlPropertyKind__linear_x0020thermal_x0020expansion = 86, resqml2__ResqmlPropertyKind__luminance = 87, resqml2__ResqmlPropertyKind__luminous_x0020efficacy = 88, resqml2__ResqmlPropertyKind__luminous_x0020flux = 89, resqml2__ResqmlPropertyKind__luminous_x0020intensity = 90, resqml2__ResqmlPropertyKind__magnetic_x0020dipole_x0020moment = 91, resqml2__ResqmlPropertyKind__magnetic_x0020field_x0020strength = 92, resqml2__ResqmlPropertyKind__magnetic_x0020flux = 93, resqml2__ResqmlPropertyKind__magnetic_x0020induction = 94, resqml2__ResqmlPropertyKind__magnetic_x0020permeability = 95, resqml2__ResqmlPropertyKind__magnetic_x0020vector_x0020potential = 96, resqml2__ResqmlPropertyKind__mass = 97, resqml2__ResqmlPropertyKind__mass_x0020attenuation_x0020coefficient = 98, resqml2__ResqmlPropertyKind__mass_x0020concentration = 99, resqml2__ResqmlPropertyKind__mass_x0020flow_x0020rate = 100, resqml2__ResqmlPropertyKind__mass_x0020length = 101, resqml2__ResqmlPropertyKind__mass_x0020per_x0020energy = 102, resqml2__ResqmlPropertyKind__mass_x0020per_x0020length = 103, resqml2__ResqmlPropertyKind__mass_x0020per_x0020time_x0020per_x0020area = 104, resqml2__ResqmlPropertyKind__mass_x0020per_x0020time_x0020per_x0020length = 105, resqml2__ResqmlPropertyKind__mass_x0020per_x0020volume_x0020per_x0020length = 106, resqml2__ResqmlPropertyKind__mobility = 107, resqml2__ResqmlPropertyKind__modulus_x0020of_x0020compression = 108, resqml2__ResqmlPropertyKind__molar_x0020concentration = 109, resqml2__ResqmlPropertyKind__molar_x0020heat_x0020capacity = 110, resqml2__ResqmlPropertyKind__molar_x0020volume = 111, resqml2__ResqmlPropertyKind__mole_x0020per_x0020area = 112, resqml2__ResqmlPropertyKind__mole_x0020per_x0020time = 113, resqml2__ResqmlPropertyKind__mole_x0020per_x0020time_x0020per_x0020area = 114, resqml2__ResqmlPropertyKind__moment_x0020of_x0020force = 115, resqml2__ResqmlPropertyKind__moment_x0020of_x0020inertia = 116, resqml2__ResqmlPropertyKind__moment_x0020of_x0020section = 117, resqml2__ResqmlPropertyKind__momentum = 118, resqml2__ResqmlPropertyKind__Mu_x0020Rho = 119, resqml2__ResqmlPropertyKind__net_x0020to_x0020gross_x0020ratio = 120, resqml2__ResqmlPropertyKind__neutron_x0020API_x0020unit = 121, resqml2__ResqmlPropertyKind__nonDarcy_x0020flow_x0020coefficient = 122, resqml2__ResqmlPropertyKind__operations_x0020per_x0020time = 123, resqml2__ResqmlPropertyKind__parachor = 124, resqml2__ResqmlPropertyKind__per_x0020area = 125, resqml2__ResqmlPropertyKind__per_x0020electric_x0020potential = 126, resqml2__ResqmlPropertyKind__per_x0020force = 127, resqml2__ResqmlPropertyKind__per_x0020length = 128, resqml2__ResqmlPropertyKind__per_x0020mass = 129, resqml2__ResqmlPropertyKind__per_x0020volume = 130, resqml2__ResqmlPropertyKind__permeability_x0020length = 131, resqml2__ResqmlPropertyKind__permeability_x0020rock = 132, resqml2__ResqmlPropertyKind__permeability_x0020thickness = 133, resqml2__ResqmlPropertyKind__permeance = 134, resqml2__ResqmlPropertyKind__permittivity = 135, resqml2__ResqmlPropertyKind__pH = 136, resqml2__ResqmlPropertyKind__plane_x0020angle = 137, resqml2__ResqmlPropertyKind__Poisson_x0020ratio = 138, resqml2__ResqmlPropertyKind__pore_x0020volume = 139, resqml2__ResqmlPropertyKind__porosity = 140, resqml2__ResqmlPropertyKind__potential_x0020difference_x0020per_x0020power_x0020drop = 141, resqml2__ResqmlPropertyKind__power = 142, resqml2__ResqmlPropertyKind__power_x0020per_x0020volume = 143, resqml2__ResqmlPropertyKind__pressure = 144, resqml2__ResqmlPropertyKind__pressure_x0020per_x0020time = 145, resqml2__ResqmlPropertyKind__pressure_x0020squared = 146, resqml2__ResqmlPropertyKind__pressure_x0020squared_x0020per_x0020force_x0020time_x0020per_x0020area = 147, resqml2__ResqmlPropertyKind__pressure_x0020time_x0020per_x0020volume = 148, resqml2__ResqmlPropertyKind__productivity_x0020index = 149, resqml2__ResqmlPropertyKind__property_x0020multiplier = 150, resqml2__ResqmlPropertyKind__quantity = 151, resqml2__ResqmlPropertyKind__quantity_x0020of_x0020light = 152, resqml2__ResqmlPropertyKind__radiance = 153, resqml2__ResqmlPropertyKind__radiant_x0020intensity = 154, resqml2__ResqmlPropertyKind__relative_x0020permeability = 155, resqml2__ResqmlPropertyKind__relative_x0020power = 156, resqml2__ResqmlPropertyKind__relative_x0020time = 157, resqml2__ResqmlPropertyKind__reluctance = 158, resqml2__ResqmlPropertyKind__resistance = 159, resqml2__ResqmlPropertyKind__resistivity_x0020per_x0020length = 160, resqml2__ResqmlPropertyKind__RESQML_x0020root_x0020property = 161, resqml2__ResqmlPropertyKind__Rock_x0020Impedance = 162, resqml2__ResqmlPropertyKind__rock_x0020permeability = 163, resqml2__ResqmlPropertyKind__rock_x0020volume = 164, resqml2__ResqmlPropertyKind__saturation = 165, resqml2__ResqmlPropertyKind__second_x0020moment_x0020of_x0020area = 166, resqml2__ResqmlPropertyKind__shear_x0020modulus = 167, resqml2__ResqmlPropertyKind__solid_x0020angle = 168, resqml2__ResqmlPropertyKind__solution_x0020gas_oil_x0020ratio = 169, resqml2__ResqmlPropertyKind__specific_x0020activity_x0020_x0028of_x0020radioactivity_x0029 = 170, resqml2__ResqmlPropertyKind__specific_x0020energy = 171, resqml2__ResqmlPropertyKind__specific_x0020heat_x0020capacity = 172, resqml2__ResqmlPropertyKind__specific_x0020productivity_x0020index = 173, resqml2__ResqmlPropertyKind__specific_x0020volume = 174, resqml2__ResqmlPropertyKind__surface_x0020density = 175, resqml2__ResqmlPropertyKind__temperature_x0020per_x0020length = 176, resqml2__ResqmlPropertyKind__temperature_x0020per_x0020time = 177, resqml2__ResqmlPropertyKind__thermal_x0020conductance = 178, resqml2__ResqmlPropertyKind__thermal_x0020conductivity = 179, resqml2__ResqmlPropertyKind__thermal_x0020diffusivity = 180, resqml2__ResqmlPropertyKind__thermal_x0020insulance = 181, resqml2__ResqmlPropertyKind__thermal_x0020resistance = 182, resqml2__ResqmlPropertyKind__thermodynamic_x0020temperature = 183, resqml2__ResqmlPropertyKind__thickness = 184, resqml2__ResqmlPropertyKind__time = 185, resqml2__ResqmlPropertyKind__time_x0020per_x0020length = 186, resqml2__ResqmlPropertyKind__time_x0020per_x0020volume = 187, resqml2__ResqmlPropertyKind__transmissibility = 188, resqml2__ResqmlPropertyKind__unit_x0020productivity_x0020index = 189, resqml2__ResqmlPropertyKind__unitless = 190, resqml2__ResqmlPropertyKind__vapor_x0020oil_gas_x0020ratio = 191, resqml2__ResqmlPropertyKind__velocity = 192, resqml2__ResqmlPropertyKind__volume = 193, resqml2__ResqmlPropertyKind__volume_x0020flow_x0020rate = 194, resqml2__ResqmlPropertyKind__volume_x0020length_x0020per_x0020time = 195, resqml2__ResqmlPropertyKind__volume_x0020per_x0020area = 196, resqml2__ResqmlPropertyKind__volume_x0020per_x0020length = 197, resqml2__ResqmlPropertyKind__volume_x0020per_x0020time_x0020per_x0020area = 198, resqml2__ResqmlPropertyKind__volume_x0020per_x0020time_x0020per_x0020length = 199, resqml2__ResqmlPropertyKind__volume_x0020per_x0020time_x0020per_x0020time = 200, resqml2__ResqmlPropertyKind__volume_x0020per_x0020time_x0020per_x0020volume = 201, resqml2__ResqmlPropertyKind__volume_x0020per_x0020volume = 202, resqml2__ResqmlPropertyKind__volumetric_x0020heat_x0020transfer_x0020coefficient = 203, resqml2__ResqmlPropertyKind__volumetric_x0020thermal_x0020expansion = 204, resqml2__ResqmlPropertyKind__work = 205, resqml2__ResqmlPropertyKind__Young_x0020modulus = 206 };
	enum resqml2__FluidContact { resqml2__FluidContact__free_x0020water_x0020contact = 0, resqml2__FluidContact__gas_x0020oil_x0020contact = 1, resqml2__FluidContact__gas_x0020water_x0020contact = 2, resqml2__FluidContact__seal = 3, resqml2__FluidContact__water_x0020oil_x0020contact = 4 };
	enum resqml2__SurfaceRole { resqml2__SurfaceRole__map = 0, resqml2__SurfaceRole__pick = 1 };
}

namespace common
{
	class EpcDocument;
}

namespace witsml1_4_1_1 {
	class Wellbore;
	class Trajectory;
	class Log;
	class FormationMarker;
}

#ifdef SWIGPYTHON
namespace resqml2_0_1
{
	%typemap(out) AbstractObject*, AbstractFeature*, AbstractFeatureInterpretation*, AbstractRepresentation*, AbstractValuesProperty*, WellboreFrameRepresentation*, AbstractLocal3dCrs* {
		// Check potential downcasting
		swig_type_info * const outtype = SWIG_TypeQuery(("resqml2_0_1::" + result->getXmlTag() + " *").c_str());
		resultobj = SWIG_NewPointerObj(SWIG_as_voidptr(result), outtype, 0);
	}
}
#endif
#ifdef SWIGJAVA
	%include "swigResqml2_0_1JavaInclude.i"
#endif
#ifdef SWIGCSHARP
	%include "swigResqml2_0_1CsInclude.i"
#endif
#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace resqml2_0_1::AbstractObject;
	%nspace resqml2_0_1::AbstractResqmlDataObject;
	%nspace resqml2_0_1::Activity;
	%nspace resqml2_0_1::ActivityTemplate;
	%nspace resqml2_0_1::EpcExternalPartReference;
	%nspace resqml2_0_1::AbstractHdfProxy;
	%nspace resqml2_0_1::HdfProxy;
	%nspace resqml2_0_1::AbstractLocal3dCrs;
	%nspace resqml2_0_1::LocalDepth3dCrs;
	%nspace resqml2_0_1::LocalTime3dCrs ;
	%nspace resqml2_0_1::MdDatum;
	%nspace resqml2_0_1::AbstractFeature;
	%nspace resqml2_0_1::AbstractGeologicFeature;
	%nspace resqml2_0_1::GeologicUnitFeature;
	%nspace resqml2_0_1::BoundaryFeature;
	%nspace resqml2_0_1::GeneticBoundaryFeature;
	%nspace resqml2_0_1::Horizon;
	%nspace resqml2_0_1::TectonicBoundaryFeature;
	%nspace resqml2_0_1::Fault;
	%nspace resqml2_0_1::Fracture;
	%nspace resqml2_0_1::AbstractTechnicalFeature;
	%nspace resqml2_0_1::SeismicLineSetFeature;
	%nspace resqml2_0_1::SeismicLineFeature;
	%nspace resqml2_0_1::SeismicLatticeFeature;
	%nspace resqml2_0_1::WellboreFeature;
	%nspace resqml2_0_1::OrganizationFeature;
	%nspace resqml2_0_1::AbstractFeatureInterpretation;
	%nspace resqml2_0_1::GenericFeatureInterpretation;
	%nspace resqml2_0_1::BoundaryFeatureInterpretation;
	%nspace resqml2_0_1::FaultInterpretation;
	%nspace resqml2_0_1::HorizonInterpretation;
	%nspace resqml2_0_1::WellboreInterpretation;
	%nspace resqml2_0_1::AbstractOrganizationInterpretation;
	%nspace resqml2_0_1::StructuralOrganizationInterpretation;
	%nspace resqml2_0_1::StratigraphicUnitFeature;
	%nspace resqml2_0_1::StratigraphicUnitInterpretation;
	%nspace resqml2_0_1::StratigraphicColumnRankInterpretation;
	%nspace resqml2_0_1::StratigraphicOccurrenceInterpretation;
	%nspace resqml2_0_1::StratigraphicColumn;
	%nspace resqml2_0_1::EarthModelInterpretation;
	%nspace resqml2_0_1::AbstractRepresentation;
	%nspace resqml2_0_1::SubRepresentation;
	%nspace resqml2_0_1::PolylineSetRepresentation;
	%nspace resqml2_0_1::PointSetRepresentation;
	%nspace resqml2_0_1::PolylineRepresentation;
	%nspace resqml2_0_1::AbstractSurfaceRepresentation;
	%nspace resqml2_0_1::Grid2dRepresentation;
	%nspace resqml2_0_1::Grid2dSetRepresentation;
	%nspace resqml2_0_1::TriangulatedSetRepresentation;
	%nspace resqml2_0_1::WellboreTrajectoryRepresentation;
	%nspace resqml2_0_1::WellboreFrameRepresentation;
	%nspace resqml2_0_1::WellboreMarker;
	%nspace resqml2_0_1::WellboreMarkerFrameRepresentation;
	%nspace resqml2_0_1::RepresentationSetRepresentation;
	%nspace resqml2_0_1::NonSealedSurfaceFrameworkRepresentation;
	%nspace resqml2_0_1::SealedSurfaceFrameworkRepresentation;
	%nspace resqml2_0_1::AbstractGridRepresentation;
	%nspace resqml2_0_1::AbstractColumnLayerGridRepresentation;
	%nspace resqml2_0_1::UnstructuredGridRepresentation;
	%nspace resqml2_0_1::GridConnectionSetRepresentation;
	%nspace resqml2_0_1::TimeSeries;
	%nspace resqml2_0_1::PropertyKind;
	%nspace resqml2_0_1::StringTableLookup;
	%nspace resqml2_0_1::AbstractProperty;
	%nspace resqml2_0_1::AbstractValuesProperty;
	%nspace resqml2_0_1::CommentProperty;
	%nspace resqml2_0_1::ContinuousProperty;
	%nspace resqml2_0_1::ContinuousPropertySeries;
	%nspace resqml2_0_1::DiscreteProperty;
	%nspace resqml2_0_1::DiscretePropertySeries;
	%nspace resqml2_0_1::CategoricalProperty;
	%nspace resqml2_0_1::CategoricalPropertySeries;
	%nspace resqml2_0_1::PropertyKindMapper;
	%nspace resqml2_0_1::FrontierFeature;
	%nspace resqml2_0_1::PlaneSetRepresentation;
	%nspace resqml2_0_1::FluidBoundaryFeature;
	%nspace resqml2_0_1::AbstractIjkGridRepresentation;
	%nspace resqml2_0_1::IjkGridExplicitRepresentation;
	%nspace resqml2_0_1::IjkGridLatticeRepresentation;
	%nspace resqml2_0_1::IjkGridParametricRepresentation;
	%nspace resqml2_0_1::IjkGridNoGeometryRepresentation;
#endif

namespace resqml2_0_1
{
	%nodefaultctor; // Disable creation of default constructors
		
	class Activity;
#ifdef SWIGPYTHON
	%rename(Resqml2_0AbstractObject) AbstractObject;
#endif
	class AbstractObject
	{
	public:
		common::EpcDocument* getEpcDocument() const;
	
		std::string getUuid() const;
		std::string getTitle() const;
		std::string getEditor() const;
		time_t getCreation() const;
		std::string getOriginator() const;
		std::string getDescription() const;
		time_t getLastUpdate() const;
		std::string getFormat() const;
		std::string getDescriptiveKeywords() const;
		
		void setUuid(const std::string & uuid);
		void setMetadata(const std::string & guid, const std::string & title, const std::string & editor, const time_t & creation, const std::string & originator,
				const std::string & description, const time_t & lastUpdate, const std::string & format, const std::string & descriptiveKeywords);
		void setTitle(const std::string & title);
		void setEditor(const std::string & editor);
		void setCreation(const time_t & creation);
		void setOriginator(const std::string & originator);
		void setDescription(const std::string & description);
		void setLastUpdate(const time_t & lastUpdate);
		void setFormat(const std::string & format);
		void setDescriptiveKeywords(const std::string & descriptiveKeywords);
				
		std::string getXmlTag() const;
		
		void addAlias(const std::string & authority, const std::string & title);
		unsigned int getAliasCount() const;
		std::string getAliasAuthorityAtIndex(const unsigned int & index) const;
		std::string getAliasTitleAtIndex(const unsigned int & index) const;
		
		const std::vector<Activity*> & getActivitySet() const;
	};

	class AbstractResqmlDataObject : public AbstractObject
	{
	public:
		void addOrSetExtraMetadata(const std::string & key, const std::string & value);
		std::string getExtraMetadata(const std::string & key);
		
		unsigned int getExtraMetadataCount() const;
		std::string getExtraMetadataKeyAtIndex(const unsigned int & index) const;
		std::string getExtraMetadataStringValueAtIndex(const unsigned int & index) const;
	};
	
	//************************************
	//************ Activity **************
	//************************************

	class ActivityTemplate : public AbstractResqmlDataObject
	{
	public:
		void pushBackParameter(const std::string title,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs);
		void pushBackParameter(const std::string title,
			const gsoap_resqml2_0_1::resqml2__ParameterKind & kind,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs);
		void pushBackParameter(const std::string title,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs,
			const std::string & resqmlObjectContentType);
		bool isAnExistingParameter(const std::string & paramTitle) const;
		const unsigned int getParameterCount() const;
		const std::string & getParameterTitle(const unsigned int & index) const;
		const bool & getParameterIsInput(const unsigned int & index) const;
		const bool & getParameterIsInput(const std::string & paramTitle) const;
		const bool & getParameterIsOutput(const unsigned int & index) const;
		const bool & getParameterIsOutput(const std::string & paramTitle) const;
		const LONG64 getParameterMinOccurences(const unsigned int & index) const;
		const LONG64 getParameterMinOccurences(const std::string & paramTitle) const;
		const LONG64 getParameterMaxOccurences(const unsigned int & index) const;
		const LONG64 getParameterMaxOccurences(const std::string & paramTitle) const;

		const std::vector<Activity*> & getActivitySet() const;
	};

	class Activity : public AbstractResqmlDataObject
	{
	public:
		void pushBackParameter(const std::string title,
			const double & value, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom = gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc);
		void pushBackParameter(const std::string title,
			const std::string & value);
		void pushBackParameter(const std::string title,
			const LONG64 & value);
		void pushBackParameter(const std::string title,
			AbstractObject* resqmlObject);
		
		unsigned int getParameterCount() const;
		unsigned int getParameterCount(const std::string & paramTitle) const;

		const std::string & getParameterTitle(const unsigned int & index) const;

		bool isAFloatingPointQuantityParameter(const std::string & paramTitle) const;
		bool isAFloatingPointQuantityParameter(const unsigned int & index) const;
		double getFloatingPointQuantityParameterValue(const unsigned int & index) const;
		gsoap_resqml2_0_1::resqml2__ResqmlUom getFloatingPointQuantityParameterUom(const unsigned int & index) const;

		bool isAnIntegerQuantityParameter(const std::string & paramTitle) const;
		bool isAnIntegerQuantityParameter(const unsigned int & index) const;
		LONG64 getIntegerQuantityParameterValue(const unsigned int & index) const;

		bool isAStringParameter(const std::string & paramTitle) const;
		bool isAStringParameter(const unsigned int & index) const;
		const std::string & getStringParameterValue(const unsigned int & index) const;

		bool isAResqmlObjectParameter(const std::string & paramTitle) const;
		bool isAResqmlObjectParameter(const unsigned int & index) const;
		AbstractObject* getResqmlObjectParameterValue(const unsigned int & index) const;

		void setActivityTemplate(ActivityTemplate* activityTemplate);
		ActivityTemplate* getActivityTemplate() const;
	};
	
	//************************************
	//************ HDF *******************
	//************************************

	class EpcExternalPartReference : public AbstractObject
	{
	};
	
	class AbstractHdfProxy : public EpcExternalPartReference
	{
	public:
		virtual bool isOpened() = 0;
		virtual void close() = 0;
	};
	
	class HdfProxy : public AbstractHdfProxy
	{
	public:
		void setCompressionLevel(const unsigned int & newCompressionLevel);
	};

	//************************************
	//************ CRS *******************
	//************************************
	
	class AbstractLocal3dCrs : public AbstractResqmlDataObject
	{
	public:
		double getOriginOrdinal1() const;
		double getOriginOrdinal2() const;
		double getOriginDepthOrElevation() const;
		double getArealRotation() const;
		bool isDepthOriented() const;
		
		bool isProjectedCrsDefinedWithEpsg() const;
		bool isProjectedCrsUnknown() const;
		const std::string & getProjectedCrsUnknownReason() const;
		unsigned long long getProjectedCrsEpsgCode() const;
		
		bool isVerticalCrsDefinedWithEpsg() const;
		bool isVerticalCrsUnknown() const;
		const std::string & getVerticalCrsUnknownReason() const;
		unsigned long long getVerticalCrsEpsgCode() const;

		gsoap_resqml2_0_1::eml__LengthUom getProjectedCrsUnit() const;
		std::string getProjectedCrsUnitAsString() const;
		gsoap_resqml2_0_1::eml__LengthUom getVerticalCrsUnit() const;
		std::string getVerticalCrsUnitAsString() const;
		gsoap_resqml2_0_1::eml__AxisOrder2d getAxisOrder() const;
	};

	class LocalDepth3dCrs : public AbstractLocal3dCrs
	{
	public:
	};

	class LocalTime3dCrs : public AbstractLocal3dCrs
	{
	public:
		gsoap_resqml2_0_1::eml__TimeUom getUnit() const;
		std::string getUnitAsString() const;
	};
	
	class MdDatum : public AbstractResqmlDataObject
	{
	public:
		std::string getLocalCrsUuid() const;
		AbstractLocal3dCrs * getLocalCrs();
		
		double getX() const;
		double getXInGlobalCrs() const;
		double getY() const;
		double getYInGlobalCrs() const;
		double getZ() const;
		double getZInGlobalCrs() const;

		gsoap_resqml2_0_1::resqml2__MdReference getOriginKind() const;
	};
	
	//************************************
	//************ FEATURE ***************
	//************************************

	class AbstractFeatureInterpretation;
	class AbstractFeature : public AbstractResqmlDataObject
	{
	public:
		unsigned int getInterpretationCount() const;
		AbstractFeatureInterpretation* getInterpretation(const unsigned int & index) const;
	};

	class AbstractGeologicFeature : public AbstractFeature
	{
	};

	class BoundaryFeature : public AbstractGeologicFeature
	{
	};
	
	class GeologicUnitFeature : public AbstractGeologicFeature
	{
	};

	class GeneticBoundaryFeature : public BoundaryFeature
	{
	};

	class Horizon : public GeneticBoundaryFeature
	{
	};

	class TectonicBoundaryFeature : public BoundaryFeature
	{
	public:
		bool isAFracture() const;
	};

	class Fault : public TectonicBoundaryFeature
	{
	};

	class Fracture : public TectonicBoundaryFeature
	{
	};

	class AbstractTechnicalFeature : public AbstractFeature
	{
	};
	
	class SeismicLineSetFeature : public AbstractTechnicalFeature
	{
	};

	class SeismicLineFeature : public AbstractTechnicalFeature
	{
	public:
		int getTraceIndexIncrement() const;
		int getFirstTraceIndex() const;
		unsigned int getTraceCount() const;
		
		SeismicLineSetFeature* getSeismicLineSet();
		void setSeismicLineSet(class SeismicLineSetFeature * seisLineSet);
	};

	class SeismicLatticeFeature : public AbstractTechnicalFeature
	{
	public:
		int getCrosslineIncrement() const;
		int getInlineIncrement() const;
		int getOriginCrossline() const;
		int getOriginInline() const;
	};

	class WellboreFeature : public AbstractTechnicalFeature
	{
	public:
		witsml1_4_1_1::Wellbore* getWitsmlWellbore();
		void setWitsmlWellbore(witsml1_4_1_1::Wellbore * wellbore);
	};
	
	class OrganizationFeature : public AbstractGeologicFeature
	{
	};
	
	class FrontierFeature : public AbstractTechnicalFeature
	{
	};
	
	class StratigraphicUnitFeature : public GeologicUnitFeature
	{
	public:
	};
	
	class FluidBoundaryFeature : public BoundaryFeature
	{
	public:
	};

	//************************************
	//************ INTERPRETATION ********
	//************************************

	class AbstractRepresentation;
	class WellboreMarkerFrameRepresentation;
	class AbstractFeatureInterpretation : public AbstractResqmlDataObject
	{
	public:
		unsigned int			getRepresentationCount() const;
		AbstractFeature*		getInterpretedFeature();
		AbstractRepresentation* getRepresentation(const unsigned int & index) const;
		std::string 			getInterpretedFeatureUuid() const;
	};

	class GenericFeatureInterpretation : public AbstractFeatureInterpretation
	{
	};
	
	class BoundaryFeatureInterpretation : public AbstractFeatureInterpretation
	{
	};
	
	class FaultInterpretation : public BoundaryFeatureInterpretation
	{
	public: 
		void pushBackThrowInterpretation(const gsoap_resqml2_0_1::resqml2__ThrowKind & throwKind);
	};

	class HorizonInterpretation : public BoundaryFeatureInterpretation
	{
	};
	
	class WellboreTrajectoryRepresentation;
	class WellboreInterpretation : public AbstractFeatureInterpretation
	{
	public:
		bool isDrilled() const;
		std::vector<WellboreTrajectoryRepresentation*> getWellboreTrajectoryRepresentationSet() const;
	};
	
	class StratigraphicUnitInterpretation : public AbstractFeatureInterpretation
	{
	};
	
	class AbstractOrganizationInterpretation : public AbstractFeatureInterpretation
	{
	public:
		void pushBackBinaryContact(const gsoap_resqml2_0_1::resqml2__ContactRelationship & kind, AbstractFeatureInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactVerb & verb, AbstractFeatureInterpretation* directObject);
		void pushBackBinaryContact(const gsoap_resqml2_0_1::resqml2__ContactRelationship & kind, AbstractFeatureInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactVerb & verb, AbstractFeatureInterpretation* directObject,
				const gsoap_resqml2_0_1::resqml2__ContactSide & directObjectQualifier);
	};
	
	class StructuralOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:
		void pushBackFaultInterpretation(FaultInterpretation * faultInterpretation);
		void pushBackHorizonInterpretation(HorizonInterpretation * horizonInterpretation, const int & stratigraphicRank);
		void pushBackTopFrontierInterpretation(AbstractFeatureInterpretation * topFrontierInterpretation);
        void pushBackBottomFrontierInterpretation(AbstractFeatureInterpretation * bottomFrontierInterpretation);
        void pushBackSideFrontierInterpretation(AbstractFeatureInterpretation * sideFrontierInterpretation);
		
		unsigned int getFaultInterpretationCount() const;
		FaultInterpretation* getFaultInterpretation(const unsigned int & index);
	};
	
	class StratigraphicOccurrenceInterpretation;
	class StratigraphicColumnRankInterpretation : public AbstractOrganizationInterpretation
	{
	public:
		void pushBackStratiUnitInterpretation(StratigraphicUnitInterpretation * stratiUnitInterpretation);
		void pushBackStratigraphicBinaryContact(StratigraphicUnitInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactMode & subjectContactMode,
			StratigraphicUnitInterpretation* directObject, const gsoap_resqml2_0_1::resqml2__ContactMode & directObjectMode,
			class HorizonInterpretation * partOf = NULL);
			
		unsigned int getContactCount() const;
		gsoap_resqml2_0_1::resqml2__ContactMode getSubjectContactModeOfContact(const unsigned int & contactIndex) const;
		gsoap_resqml2_0_1::resqml2__ContactMode getDirectObjectContactModeOfContact(const unsigned int & contactIndex) const;
		HorizonInterpretation* getHorizonInterpretationOfContact(const unsigned int & contactIndex) const;
		bool isAChronoStratiRank() const;
		StratigraphicUnitInterpretation* getSubjectOfContact(const unsigned int & contactIndex) const;
		StratigraphicUnitInterpretation* getDirectObjectOfContact(const unsigned int & contactIndex) const;
		std::vector<StratigraphicUnitInterpretation*> getStratigraphicUnitInterpretationSet() const;
        std::vector<HorizonInterpretation*> getHorizonInterpretationSet() const;
		std::vector<StratigraphicOccurrenceInterpretation*> getStratigraphicOccurrenceInterpretationSet() const;
	};
	
	class StratigraphicOccurrenceInterpretation : public AbstractOrganizationInterpretation
	{
	public:
		void setStratigraphicColumnRankInterpretation(StratigraphicColumnRankInterpretation * stratiColumnRankInterp);
		StratigraphicColumnRankInterpretation * getStratigraphicColumnRankInterpretation() const;
		std::string getStratigraphicColumnRankInterpretationUuid() const;
		
		std::vector<class WellboreMarkerFrameRepresentation*> getWellboreMarkerFrameRepresentationSet() const;
	};
	
	class StratigraphicColumn : public AbstractResqmlDataObject
	{
	public:
		void pushBackStratiColumnRank(StratigraphicColumnRankInterpretation * stratiColumnRank);
		std::vector<class StratigraphicColumnRankInterpretation*> getStratigraphicColumnRankInterpretationSet() const;
	};
	
	class EarthModelInterpretation : public AbstractFeatureInterpretation
	{
	public:
		void setStructuralOrganizationInterpretation(StructuralOrganizationInterpretation * structOrganization);
		void setStratiColumn(StratigraphicColumn * stratiColumn);
	};

	//************************************
	//************ REPRESENTATION ********
	//************************************

	class AbstractValuesProperty;
	class SubRepresentation;
	class RepresentationSetRepresentation;
	class AbstractRepresentation : public AbstractResqmlDataObject
	{
	public:
		AbstractFeatureInterpretation* getInterpretation() const;
		std::string getInterpretationUuid() const;
		AbstractLocal3dCrs * getLocalCrs();
		std::string getLocalCrsUuid() const;
		AbstractHdfProxy * getHdfProxy();
		std::string getHdfProxyUuid() const;
		unsigned int getValuesPropertyCount() const;
		AbstractValuesProperty* getValuesProperty(const unsigned int & index) const;
		
		unsigned int getSubRepresentationCount() const;
		class SubRepresentation* getSubRepresentation(const unsigned int & index) const;
		unsigned int getFaultSubRepresentationCount() const;
		SubRepresentation* getFaultSubRepresentation(const unsigned int & index) const;

		virtual ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const = 0;
		ULONG64 getXyzPointCountOfAllPatches() const;
		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;
		void getXyzPointsOfPatchInGlobalCrs(const unsigned int & patchIndex, double * xyzPoints) const;
		void getXyzPointsOfAllPatches(double * xyzPoints) const;
		void getXyzPointsOfAllPatchesInGlobalCrs(double * xyzPoints) const;
		virtual unsigned int getPatchCount() const;
		
		AbstractRepresentation* getSeismicSupportOfPatch(const unsigned int & patchIndex);
		void getSeismicLineAbscissaOfPointsOfPatch(const unsigned int & patchIndex, double* values);
		void addSeismic2dCoordinatesToPatch(const unsigned int patchIndex, double * lineAbscissa, const unsigned int & pointCount,
			AbstractRepresentation * seismicSupport, AbstractHdfProxy * proxy);
		void addSeismic3dCoordinatesToPatch(const unsigned int patchIndex, double * inlines, double * crosslines, const unsigned int & pointCount,
			AbstractRepresentation * seismicSupport, AbstractHdfProxy * proxy);
		void addSeismic3dCoordinatesToPatch(const unsigned int patchIndex, const double & startInline, const double & incrInline, const unsigned int & countInline,
			const double & startCrossline, const double & incrCrossline, const unsigned int & countCrossline,
			AbstractRepresentation * seismicSupport);

		void pushBackIntoRepresentationSet(RepresentationSetRepresentation * repSet);
	};
	
	class SubRepresentation : public AbstractRepresentation
	{
	public:
		void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & elementCount, unsigned int * elementIndices, AbstractHdfProxy * proxy);
		void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind0, const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind1,
			const ULONG64 & elementCount,
			unsigned int * elementIndices0, unsigned int * elementIndices1,
			AbstractHdfProxy * proxy);
		
		bool isElementPairBased(const unsigned int & patchIndex) const;
		
		gsoap_resqml2_0_1::resqml2__IndexableElements getElementKindOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const;
		ULONG64 getElementCountOfPatch(const unsigned int & patchIndex) const;
		void getElementIndicesOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex, unsigned int * elementIndices) const;
	};

	class PolylineSetRepresentation : public AbstractRepresentation
	{
	public:
		unsigned int getPolylineCountOfPatch(const unsigned int & patchIndex) const;
		unsigned int getPolylineCountOfAllPatches() const;
		void getNodeCountPerPolylineInPatch(const unsigned int & patchIndex, unsigned int * nodeCountPerPolyline) const;
		void getNodeCountPerPolylineOfAllPatches(unsigned int * nodeCountPerPolyline) const;
		void pushBackGeometryPatch(
				unsigned int * NodeCountPerPolyline, double * nodes,
				const unsigned int & polylineCount, const bool & allPolylinesClosedFlag,
				AbstractHdfProxy * proxy);
		void pushBackGeometryPatch(
				unsigned int * NodeCountPerPolyline, double * nodes,
				const unsigned int & polylineCount, bool * polylineClosedFlags,
				AbstractHdfProxy * proxy);
				
		bool areAllPolylinesClosedOfPatch(const unsigned int & patchIndex) const;
		bool areAllPolylinesClosedOfAllPatches() const;
		bool areAllPolylinesNonClosedOfPatch(const unsigned int & patchIndex) const;
		bool areAllPolylinesNonClosedOfAllPatches() const;
		void getClosedFlagPerPolylineOfPatch(const unsigned int & patchIndex, bool * closedFlagPerPolyline) const;
		void getClosedFlagPerPolylineOfAllPatches(bool * closedFlagPerPolyline) const;
		bool hasALineRole() const;
		gsoap_resqml2_0_1::resqml2__LineRole getLineRole() const;
		void setLineRole(const gsoap_resqml2_0_1::resqml2__LineRole & lineRole);
	};
	
	class PointSetRepresentation : public AbstractRepresentation
	{
	public:
		void pushBackGeometryPatch(
			const unsigned int & xyzPointCount, double * xyzPoints,
			AbstractHdfProxy * proxy);
	};
	
	class PlaneSetRepresentation : public AbstractRepresentation
	{
	public:
		void pushBackHorizontalPlaneGeometryPatch(const double & zCoordinate);
		void pushBackTiltedPlaneGeometryPatch(const double & x1, const double & y1, const double & z1,
			const double & x2, const double & y2, const double & z2,
			const double & x3, const double & y3, const double & z3);
	};

	class PolylineRepresentation : public AbstractRepresentation
	{
	public:
		void setGeometry(double * points, const unsigned int & pointCount, AbstractHdfProxy * proxy);
		bool isClosed() const;
		bool hasALineRole() const;
		gsoap_resqml2_0_1::resqml2__LineRole getLineRole() const;
		void setLineRole(const gsoap_resqml2_0_1::resqml2__LineRole & lineRole);
	};
	
	class AbstractSurfaceRepresentation : public AbstractRepresentation
	{
	public:
		void setSurfaceRole(const gsoap_resqml2_0_1::resqml2__SurfaceRole & surfaceRole);
		const gsoap_resqml2_0_1::resqml2__SurfaceRole & getSurfaceRole() const;
		void pushBackOuterRing(PolylineRepresentation * outerRing);
	};
	
	class Grid2dRepresentation : public AbstractSurfaceRepresentation
	{
	public:
		ULONG64 getNodeCountAlongIAxis() const;
		ULONG64 getNodeCountAlongJAxis() const;
		
		double getXOrigin() const;
		double getYOrigin() const;
		double getXOriginInGlobalCrs() const;
		double getYOriginInGlobalCrs() const;
		double getXJOffset() const;
		double getYJOffset() const;
		double getXJOffsetInGlobalCrs() const;
		double getYJOffsetInGlobalCrs() const;
		double getXIOffset() const;
		double getYIOffset() const;
		double getXIOffsetInGlobalCrs() const;
		double getYIOffsetInGlobalCrs() const;
		double getJSpacing() const;
		double getISpacing() const;
		
		void getZValues(double * values) const;
		void getZValuesInGlobalCrs(double * values) const;
		
		int getIndexOriginOnSupportingRepresentation() const;
		int getIndexOriginOnSupportingRepresentation(const unsigned int & dimension) const;
		int getNodeCountOnSupportingRepresentation(const unsigned int & dimension) const;
		int getIndexOffsetOnSupportingRepresentation(const unsigned int & dimension) const;
		
		void setGeometryAsArray2dOfLatticePoints3d(
			const unsigned int & numPointsInFastestDirection, const unsigned int & numPointsInSlowestDirection,
			const double & xOrigin, const double & yOrigin, const double & zOrigin,
			const double & xOffsetInFastestDirection, const double & yOffsetInFastestDirection, const double & zOffsetInFastestDirection,
			const double & xOffsetInSlowestDirection, const double & yOffsetInSlowestDirection, const double & zOffsetInSlowestDirection,
			const double & spacingInFastestDirection, const double & spacingInSlowestDirection);

		void setGeometryAsArray2dOfExplicitZ(
			double * zValues,
			const unsigned int & numI, const unsigned int & numJ, AbstractHdfProxy * proxy,
			Grid2dRepresentation * supportingGrid2dRepresentation,
			const unsigned int & startIndexI = 0, const unsigned int & startIndexJ = 0,
			const int & indexIncrementI = 1, const int & indexIncrementJ = 1);
			
		void setGeometryAsArray2dOfExplicitZ(
			double * zValues,
			const unsigned int & numI, const unsigned int & numJ, AbstractHdfProxy * proxy,
			const double & originX, const double & originY, const double & originZ,
			const double & offsetIX, const double & offsetIY, const double & offsetIZ, const double & spacingI,
			const double & offsetJX, const double & offsetJY, const double & offsetJZ, const double & spacingJ);
		
		Grid2dRepresentation*  getSupportingRepresentation();
		std::string getSupportingRepresentationUuid() const;
	};
	
	class Grid2dSetRepresentation : public AbstractSurfaceRepresentation
	{
	public:
		unsigned int getNodeCountAlongIAxis(const unsigned int & patchIndex) const;
		unsigned int getNodeCountAlongJAxis(const unsigned int & patchIndex) const;
		
		void getZValuesOfPatch(const unsigned int & patchIndex, double* values) const;
		void getZValuesOfPatchInGlobalCrs(const unsigned int & patchIndex, double* values) const;
		void pushBackGeometryPatch(
				double * zValues,
				const unsigned int & numI, const unsigned int & numJ, AbstractHdfProxy * proxy,
				Grid2dRepresentation * supportingGrid2dRepresentation,
				const unsigned int & startIndexI = 0, const unsigned int & startIndexJ = 0,
				const int & indexIncrementI = 1, const int & indexIncrementJ = 1);
		
		std::string getSupportingRepresentationUuid(const unsigned int & patchIndex) const;
		Grid2dRepresentation * getSupportingRepresentation(const unsigned int & patchIndex) {return supportingRepresentationSet[patchIndex];}
		int getIndexOriginOnSupportingRepresentation(const unsigned int & patchIndex, const unsigned int & dimension) const;
		int getNodeCountOnSupportingRepresentation(const unsigned int & patchIndex, const unsigned int & dimension) const;
		int getIndexOffsetOnSupportingRepresentation(const unsigned int & patchIndex, const unsigned int & dimension) const;
	};
	
	class TriangulatedSetRepresentation : public AbstractSurfaceRepresentation
	{
	public:
		unsigned int getTriangleCountOfPatch(const unsigned int & patchIndex) const;
		unsigned int getTriangleCountOfAllPatches() const;
		void getTriangleNodeIndicesOfPatch(const unsigned int & patchIndex, unsigned int * triangleNodeIndices) const;
		void getTriangleNodeIndicesOfAllPatches(unsigned int * triangleNodeIndices) const;
		void pushBackTrianglePatch(const unsigned int & NodeCount, double * nodes, const unsigned int & triangleCount, unsigned int * triangleNodeIndices, AbstractHdfProxy * proxy);
	};
	
	class WellboreFrameRepresentation;
	class  WellboreTrajectoryRepresentation : public AbstractRepresentation
	{
	public:
		unsigned int getWellboreFrameRepresentationCount() const;
		WellboreFrameRepresentation* getWellboreFrameRepresentation(const unsigned int & index) const;
		
		std::string getMdDatumUuid() const;
		MdDatum * getMdDatum();
		
		void setGeometry(double * controlPoints, const double & startMd, const double & endMd, const unsigned int & controlPointCount, const int & lineKind, class AbstractHdfProxy * proxy);
		void setGeometry(double * controlPoints,
			double* controlPointParameters, const unsigned int & controlPointCount,
			AbstractHdfProxy * proxy);
		void setGeometry(double * controlPoints,
			double * tangentVectors, double* controlPointParameters, const unsigned int & controlPointCount,
			AbstractHdfProxy * proxy);
			
		void addParentTrajectory(const double & kickoffMd, const double & parentMd, WellboreTrajectoryRepresentation* parentTrajRep);

		int getGeometryKind() const;

		bool hasTangentVectors() const;
		void getTangentVectors(double* tangentVectors);

		bool hasMdValues() const;
		void getMdValues(double* values);
		double getStartMd() const;
		double getFinishMd() const;

		void setWitsmlTrajectory(witsml1_4_1_1::Trajectory * witsmlTraj);
		witsml1_4_1_1::Trajectory * getWitsmlTrajectory();
	};
	
	class WellboreFrameRepresentation : public AbstractRepresentation
	{
	public:
		void setMdValues(double * mdValues, const unsigned int & mdValueCount, class AbstractHdfProxy * proxy);
		void setMdValues(const double & firstMdValue, const double & incrementMdValue, const unsigned int & mdValueCount);

		bool areMdValuesRegularlySpaced() const;
		double getMdConstantIncrementValue() const;
		double getMdFirstValue() const;

		unsigned int getMdValuesCount() const;
		AbstractValuesProperty::hdfDatatypeEnum getMdHdfDatatype() const;
		void getMdAsDoubleValues(double * values);
		void getMdAsFloatValues(float * values);
		
		std::string getWellboreTrajectoryUuid() const;
		WellboreTrajectoryRepresentation* getWellboreTrajectory();

		void setWitsmlLog(witsml1_4_1_1::Log * witsmlLogToSet);
		witsml1_4_1_1::Log* getWitsmlLog();
	};
	
	class WellboreMarker : public AbstractResqmlDataObject
	{
	public:
		bool hasAGeologicBoundaryKind();
		gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind getGeologicBoundaryKind();
		BoundaryFeatureInterpretation* getBoundaryFeatureInterpretation() const;
		std::string getBoundaryFeatureInterpretationUuid() const;
		void setBoundaryFeatureInterpretation(BoundaryFeatureInterpretation* interp);
	};
	
	class WellboreMarkerFrameRepresentation : public WellboreFrameRepresentation
	{
	public:
		WellboreMarker* pushBackNewWellboreMarker(const std::string & guid, const std::string & title);
		WellboreMarker* pushBackNewWellboreMarker(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind & geologicBoundaryKind);
		
		unsigned int getWellboreMarkerCount();
		const std::vector<WellboreMarker*> & getWellboreMarkerSet() const;

		void setIntervalStratigraphicUnits(unsigned int * stratiUnitIndices, const unsigned int & nullValue, class StratigraphicOccurrenceInterpretation* stratiOccurenceInterp);
		StratigraphicOccurrenceInterpretation* getStratigraphicOccurrenceInterpretation();

		void setWitsmlFormationMarker(const unsigned int & resqmlMarkerIndex, witsml1_4_1_1::FormationMarker * witsmlFormationMarker);
	};
	
	class RepresentationSetRepresentation : public AbstractRepresentation
	{
	public:
	};
	
	class NonSealedSurfaceFrameworkRepresentation : public RepresentationSetRepresentation
	{
	public:
		void pushBackNonSealedContactRepresentation(const unsigned int & pointCount, double * points, class AbstractLocal3dCrs* localCrs, class AbstractHdfProxy * proxy);
	};
	
	class SealedSurfaceFrameworkRepresentation : public RepresentationSetRepresentation
	{
	public:
	};

	class GridConnectionSetRepresentation;
	class AbstractGridRepresentation : public AbstractRepresentation
	{
	public:
		unsigned int getGridConnectionSetRepresentationCount() const;
		GridConnectionSetRepresentation* getGridConnectionSetRepresentation(const unsigned int & index) const;
		virtual ULONG64 getCellCount() const = 0;
	};

	class AbstractColumnLayerGridRepresentation : public AbstractGridRepresentation
	{
	public:
		unsigned int getKCellCount() const;
		void setKCellCount(const unsigned int & kCount);
	};

	class UnstructuredGridRepresentation : public AbstractGridRepresentation
	{
	public:
		ULONG64 getFaceCount() const;
		void getFaceIndicesOfCells(ULONG64 * faceIndices) const;
		void getCumulativeFaceCountPerCell(ULONG64 * faceCountPerCell) const;
		void getFaceCountPerCell(ULONG64 * faceCountPerCell) const;
		bool isFaceCountOfCellsConstant() const;
		unsigned int getConstantFaceCountOfCells() const;
		
		void getNodeIndicesOfFaces(ULONG64 * nodeIndices) const;
		void getCumulativeNodeCountPerFace(ULONG64 * nodeCountPerFace) const;
		void getNodeCountPerFace(ULONG64 * nodeCountPerFace) const;
		bool isNodeCountOfFacesContant() const;
		unsigned int getConstantNodeCountOfFaces() const;
		
		void loadGeometry();
		unsigned int getFaceCountOfCell(const ULONG64 & cellIndex) const;
		unsigned int getNodeCountOfFaceOfCell(const ULONG64 & cellIndex, const unsigned int & localFaceIndex) const;
		ULONG64 * getNodeIndicesOfFaceOfCell(const ULONG64 & cellIndex, const unsigned int & localFaceIndex) const;
		void unloadGeometry();
		
		void setGeometry(const bool & isRightHanded, double * points, const unsigned int & pointCount, AbstractHdfProxy * proxy,
				unsigned int * faceIndicesPerCell, unsigned int * faceIndicesCumulativeCountPerCell, const unsigned int & faceCount,
				unsigned int * nodeIndicesPerFace, unsigned int * nodeIndicesCumulativeCountPerFace, const unsigned int & nodeCount,
				const gsoap_resqml2_0_1::resqml2__CellShape & cellShape);
		void setTetrahedraOnlyGeometry(const bool & isRightHanded, double * points, const unsigned int & pointCount, const unsigned int & faceCount, class AbstractHdfProxy * proxy,
						unsigned int * faceIndicesPerCell, unsigned int * nodeIndicesPerFace);
	};
	
	class AbstractIjkGridRepresentation : public AbstractColumnLayerGridRepresentation
	{
	public:
		enum geometryKind { UNKNOWN = 0, EXPLICIT = 1, PARAMETRIC = 2, LATTICE = 3, NO_GEOMETRY = 4 };
	
		unsigned int getICellCount() const;
		void setICellCount(const unsigned int & iCount);
		unsigned int getJCellCount() const;
		void setJCellCount(const unsigned int & jCount);
		
		unsigned int getColumnCount() const {return getICellCount() * getJCellCount();}
		unsigned int getPillarCount() const {return (getICellCount()+1) * (getJCellCount()+1);}

		bool isRightHanded() const;

		void getPillarsOfSplitCoordinateLines(unsigned int * pillarIndices, bool reverseIAxis = false, bool reverseJAxis = false) const;
		void getColumnsOfSplitCoordinateLines(unsigned int * columnIndices, bool reverseIAxis = false, bool reverseJAxis = false) const;
		void getColumnCountOfSplitCoordinateLines(unsigned int * columnIndexCountPerSplitCoordinateLine) const;
		unsigned long getSplitCoordinateLineCount() const;
		
		void getPillarGeometryIsDefined(bool * pillarGeometryIsDefined, bool reverseIAxis = false, bool reverseJAxis = false) const;
		bool hasEnabledCellInformation() const;
		void getEnabledCells(bool * enabledCells, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;
		void setEnabledCells(unsigned char* enabledCells);
		
		virtual geometryKind getGeometryKind() const = 0;
		
		UnstructuredGridRepresentation* cloneToUnstructuredGridRepresentation(const std::string & guid, const std::string & title);
	};
	
	class IjkGridLatticeRepresentation : public AbstractIjkGridRepresentation
	{
	public:
		bool isASeismicCube() const;
		bool isAFaciesCube() const;
		
		double getXOrigin() const;
		double getYOrigin() const;
		double getZOrigin() const;
		double getXOriginInGlobalCrs() const;
		double getYOriginInGlobalCrs() const;
		double getZOriginInGlobalCrs() const;
        double getXIOffset() const;
        double getYIOffset() const;
        double getZIOffset() const;
        double getXJOffset() const;
        double getYJOffset() const;
        double getZJOffset() const;
        double getXKOffset() const;
        double getYKOffset() const;
        double getZKOffset() const;
		double getISpacing() const;
        double getJSpacing() const;
        double getKSpacing() const;
        int getOriginInline() const;
        int getOriginCrossline() const;
        int getInlineIOffset() const;
        int getInlineJOffset() const;
        int getInlineKOffset() const;
        int getCrosslineIOffset() const;
        int getCrosslineJOffset() const;
        int getCrosslineKOffset() const;

		void setGeometryAsCoordinateLineNodes(const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry,
						const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind,
						const bool & isRightHanded,
						const double & originX, const double & originY, const double & originZ,
						const double & directionIX, const double & directionIY, const double & directionIZ, const double & spacingI,
						const double & directionJX, const double & directionJY, const double & directionJZ, const double & spacingJ,
						const double & directionKX, const double & directionKY, const double & directionKZ, const double & spacingK);

		void addSeismic3dCoordinatesToPatch(
						const unsigned int patchIndex,
						const double & startInline, const double & incrInline, const unsigned int & countInline,
						const double & startCrossline, const double & incrCrossline, const unsigned int & countCrossline,
			            const unsigned int & countSample, AbstractRepresentation * seismicSupport);
	};
	
	class IjkGridExplicitRepresentation : public AbstractIjkGridRepresentation
	{
	public:
		void setGeometryAsCoordinateLineNodes(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * points, class AbstractHdfProxy * proxy,
			const unsigned long & splitCoordinateLineCount = 0, unsigned int * pillarOfCoordinateLine = NULL,
			unsigned int * splitCoordinateLineColumnCumulativeCount = NULL, unsigned int * splitCoordinateLineColumns = NULL);
	};
	
	class IjkGridParametricRepresentation : public AbstractIjkGridRepresentation
	{
	public:
		unsigned int getControlPointMaxCountPerPillar() const;
		void getControlPoints(double * controlPoints, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;
		bool hasControlPointParameters() const;
		void getControlPointParameters(double * controlPointParameters, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;
		void getParametricLineKind(short * pillarKind, bool reverseIAxis = false, bool reverseJAxis= false) const;
		void getParametersOfNodes(double * parameters, bool reverseIAxis = false, bool reverseJAxis= false, bool reverseKAxis= false) const;

		void setGeometryAsParametricNonSplittedPillarNodes(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, short * pillarKind, class AbstractHdfProxy * proxy);
		void setGeometryAsParametricSplittedPillarNodes(
			const gsoap_resqml2_0_1::resqml2__PillarShape & mostComplexPillarGeometry, const gsoap_resqml2_0_1::resqml2__KDirection & kDirectionKind, const bool & isRightHanded,
			double * parameters, double * controlPoints, double * controlPointParameters, const unsigned int & controlPointMaxCountPerPillar, short * pillarKind, class AbstractHdfProxy * proxy,
			const unsigned long & splitCoordinateLineCount, unsigned int * pillarOfCoordinateLine,
			unsigned int * splitCoordinateLineColumnCumulativeCount, unsigned int * splitCoordinateLineColumns);
	};
	
	class IjkGridNoGeometryRepresentation : public AbstractIjkGridRepresentation
	{
	public:
	};
	
	class GridConnectionSetRepresentation : public AbstractRepresentation
	{
	public:
		bool isAssociatedToFaults() const;
		void getFaultIndexCumulativeCount(unsigned int * cumulativeCount) const;
		void getFaultIndices(unsigned int * faultIndices) const;
		LONG64 getFaultIndexNullValue() const;
	
		ULONG64 getCellIndexPairCount() const;
		unsigned int getCellIndexPairCountFromFaultIndex(const unsigned int & faultIndex) const;
		
		void getCellIndexPairs(ULONG64 * cellIndexPairs) const;
		void getGridConnectionSetInformationFromFaultIndex(unsigned int * cellIndexPairs, unsigned int * gridIndexPairs, int * localFaceIndexPairs, const unsigned int & faultIndex) const;
		bool hasLocalFacePerCell() const;
		void getLocalFacePerCellIndexPairs(unsigned int * localFacePerCellIndexPairs) const;
		bool isBasedOnMultiGrids() const;
		void getGridIndexPairs(unsigned int * gridIndexPairs) const;
		
		void setCellIndexPairs(const unsigned int & cellIndexPairCount, ULONG64 * cellIndexPair, const ULONG64 & nullValue, AbstractHdfProxy * proxy);
		void setLocalFacePerCellIndexPairs(const unsigned int & cellIndexPairCount, unsigned int * localFacePerCellIndexPair, const unsigned int & nullValue, AbstractHdfProxy * proxy);
		void setConnectionFaultNames(unsigned int * faultIndices, const unsigned int & faultIndiceCount, const ULONG64 & nullValue, AbstractHdfProxy * proxy);
		
		std::string getFaultInterpretationUuidFromFaultIndex(const unsigned int & faultIndex) const;
		FaultInterpretation* getFaultInterpretationFromFaultIndex(const unsigned int & faultIndex) const;
		unsigned int getFaultInterpretationCount() const;
		
		unsigned int getSupportingGridRepresentationCount() const;
		AbstractGridRepresentation* getSupportingGridRepresentation();
		std::string getSupportingGridRepresentationUuid() const;
	};

	//************************************
	//************** PROPERTY ************
	//************************************
	
	class TimeSeries : public AbstractResqmlDataObject
	{
	public:
		void pushBackTimestamp(const time_t & timestamp);
		unsigned int getTimestampIndex(const time_t & timestamp) const;
		unsigned int getTimestampCount() const;
		time_t getTimestamp(const unsigned int & index) const;
	};
	
	class PropertyKind : public AbstractResqmlDataObject
	{
	public:
		const std::string & getNamingSystem() const;
		
		const gsoap_resqml2_0_1::resqml2__ResqmlUom & getUom() const;
		std::string getUomAsString() const;
	};
	
	class StringTableLookup : public AbstractResqmlDataObject
	{
	public:
		unsigned int getItemCount() const;
		long getKeyAtIndex(const unsigned int & index) const;
		std::string getStringValueAtIndex(const unsigned int & index) const;
		std::string getStringValue(const long & longValue);
		
		void addValue(const std::string & strValue, const long & longValue);
		void setValue(const std::string & strValue, const long & longValue);
	};
	
	class AbstractProperty: public AbstractResqmlDataObject
	{
	public:
		std::string getRepresentationUuid() const;
		AbstractRepresentation* getRepresentation();
		
		std::string getHdfProxyUuid() const;
		AbstractHdfProxy* getHdfProxy();
		
		std::string getPropertyKindDescription() const;
		std::string getPropertyKindAsString() const;
		std::string getPropertyKindParentAsString() const;
		bool isAssociatedToOneStandardEnergisticsPropertyKind() const;
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getEnergisticsPropertyKind() const;
		
		std::string getLocalPropertyKindUuid() const;
		PropertyKind* getLocalPropertyKind() const;
		
		unsigned int getElementCountPerValue() const;
		
		gsoap_resqml2_0_1::resqml2__IndexableElements getAttachmentKind() const;
		
		void setTimeIndex(const unsigned int & timeIndex, TimeSeries * ts);
		void setTimeStep(const unsigned int & timeStep);
		TimeSeries* getTimeSeries() const;
		time_t getTimestamp() const;
	};
	
	class AbstractValuesProperty : public AbstractProperty
	{
	public:
		enum hdfDatatypeEnum { UNKNOWN = 0, DOUBLE = 1, FLOAT = 2, LONG = 3, ULONG = 4, INT = 5, UINT = 6, SHORT = 7, USHORT = 8, CHAR = 9, UCHAR = 10};
		AbstractValuesProperty::hdfDatatypeEnum getValuesHdfDatatype() const;
		
		long getNullValueOfPatch(const unsigned int & patchIndex);
		long getLongValuesOfPatch(const unsigned int & patchIndex, long * values);
		unsigned long getULongValuesOfPatch(const unsigned int & patchIndex, unsigned long * values);
		int getIntValuesOfPatch(const unsigned int & patchIndex, int * values);
		unsigned int getUIntValuesOfPatch(const unsigned int & patchIndex, unsigned int * values);
		short getShortValuesOfPatch(const unsigned int & patchIndex, short * values);
		unsigned short getUShortValuesOfPatch(const unsigned int & patchIndex, unsigned short * values);
		char getCharValuesOfPatch(const unsigned int & patchIndex, char * values);
		unsigned char getUCharValuesOfPatch(const unsigned int & patchIndex, unsigned char * values);
		
		unsigned int getValuesCountOfPatch (const unsigned int & patchIndex);
		unsigned int getValuesCountOfDimensionOfPatch(const unsigned int & dimIndex, const unsigned int & patchIndex);
		unsigned int getDimensionsCountOfPatch(const unsigned int & patchIndex);
		
		void createLongHdf5ArrayOfValues(
			unsigned long long* numValues, 
			const unsigned int& numArrayDimensions, 
			AbstractHdfProxy* proxy
		);
		void createLongHdf5Array3dOfValues(
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			AbstractHdfProxy * proxy
		);
		void pushBackLongHdf5SlabArray3dOfValues(
			long* values, 
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			const unsigned int& offsetInFastestDim, 
			const unsigned int& offsetInMiddleDim, 
			const unsigned int& offsetInSlowestDim, 
			AbstractHdfProxy* proxy
		);
		void pushBackLongHdf5SlabArrayOfValues(
			long * values, 
			unsigned long long * numValues, 
			unsigned long long * offsetValues, 
			const unsigned int & numArrayDimensions, 
			AbstractHdfProxy * proxy
		);
		void getLongValuesOfPatch(
			const unsigned int& patchIndex, 
			long* values, 
			unsigned long long* numValuesInEachDimension,
			unsigned long long* offsetInEachDimension, 
			const unsigned int& numArrayDimensions
		);
		void getLongValuesOf3dPatch(
			const unsigned int& patchIndex, 
			long* values, 
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			const unsigned int& offsetInFastestDim, 
			const unsigned int& offsetInMiddleDim, 
			const unsigned int& offsetInSlowestDim
		);
		
	};
	
	class CommentProperty : public AbstractValuesProperty
	{
	public:
		void pushBackStringHdf5ArrayOfValues(const std::vector<std::string> & values, AbstractHdfProxy * proxy);
		std::vector<std::string> getStringValuesOfPatch(const unsigned int & patchIndex);
	};
	
	class ContinuousProperty : public AbstractValuesProperty
	{
	public:

		const gsoap_resqml2_0_1::resqml2__ResqmlUom & getUom() const;
		std::string getUomAsString() const;
		
		void pushBackDoubleHdf5Array1dOfValues(double * values, const unsigned int & valueCount, AbstractHdfProxy * proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());
		void pushBackDoubleHdf5Array2dOfValues(double * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInSlowestDim, AbstractHdfProxy * proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());
		void pushBackDoubleHdf5Array3dOfValues(double * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInMiddleDim, const unsigned int & valueCountInSlowestDim, AbstractHdfProxy * proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());
		void pushBackDoubleHdf5ArrayOfValues(double * values, unsigned long long * numValues, const unsigned int & numArrayDimensions, AbstractHdfProxy * proxy,
			double * minimumValue = NULL, double * maximumValue = NULL);
		void pushBackFloatHdf5Array1dOfValues(float * values, const unsigned int & valueCount, AbstractHdfProxy * proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());
		void pushBackFloatHdf5Array2dOfValues(float * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInSlowestDim, AbstractHdfProxy * proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());
		void pushBackFloatHdf5Array3dOfValues(float * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInMiddleDim, const unsigned int & valueCountInSlowestDim, AbstractHdfProxy * proxy,
			const double & minimumValue = std::numeric_limits<double>::quiet_NaN(), const double & maximumValue = std::numeric_limits<double>::quiet_NaN());
		void pushBackFloatHdf5ArrayOfValues(float * values, unsigned long long * numValues, const unsigned int & numArrayDimensions, AbstractHdfProxy * proxy,
			double * minimumValue = NULL, double * maximumValue = NULL);
		void getDoubleValuesOfPatch(const unsigned int & patchIndex, double * values);
		void getFloatValuesOfPatch(const unsigned int & patchIndex, float * values);
		
		void createFloatHdf5ArrayOfValues(
			unsigned long long* numValues, 
			const unsigned int& numArrayDimensions, 
			AbstractHdfProxy* proxy
		);
		void createFloatHdf5Array3dOfValues(
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			AbstractHdfProxy * proxy
		);
		void pushBackFloatHdf5SlabArray3dOfValues(
			float* values, 
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			const unsigned int& offsetInFastestDim, 
			const unsigned int& offsetInMiddleDim, 
			const unsigned int& offsetInSlowestDim, 
			AbstractHdfProxy* proxy
		);
		void pushBackFloatHdf5SlabArrayOfValues(
			float * values, 
			unsigned long long * numValues, 
			unsigned long long * offsetValues, 
			const unsigned int & numArrayDimensions, 
			AbstractHdfProxy * proxy
		);
		void getFloatValuesOfPatch(
			const unsigned int& patchIndex, 
			float* values, 
			unsigned long long* numValuesInEachDimension,
			unsigned long long* offsetInEachDimension, 
			const unsigned int& numArrayDimensions
		);
		void getFloatValuesOf3dPatch(
			const unsigned int& patchIndex, 
			float* values, 
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			const unsigned int& offsetInFastestDim, 
			const unsigned int& offsetInMiddleDim, 
			const unsigned int& offsetInSlowestDim
		);
		
		double getMinimumValue();
		double getMaximumValue();
		
	};
	
	class ContinuousPropertySeries : public ContinuousProperty
	{
	public:
	};
	
	class DiscreteProperty : public AbstractValuesProperty
	{
	public:
		void pushBackLongHdf5Array1dOfValues(long * values, const unsigned int & valueCount, AbstractHdfProxy * proxy, const long & nullValue, const long &  minimumValue, const long &  maximumValue);
		void pushBackLongHdf5Array1dOfValues(long * values, const unsigned int & valueCount, AbstractHdfProxy * proxy, const long & nullValue);
		void pushBackLongHdf5Array2dOfValues(long * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInSlowestDim, AbstractHdfProxy * proxy, const long & nullValue, const long &  minimumValue, const long &  maximumValue);
		void pushBackLongHdf5Array2dOfValues(long * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInSlowestDim, AbstractHdfProxy * proxy, const long & nullValue);
		void pushBackLongHdf5Array3dOfValues(long * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInMiddleDim, const unsigned int & valueCountInSlowestDim, AbstractHdfProxy * proxy, const long & nullValue, const long &  minimumValue, const long &  maximumValue);
		void pushBackLongHdf5Array3dOfValues(long * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInMiddleDim, const unsigned int & valueCountInSlowestDim, AbstractHdfProxy * proxy, const long & nullValue);
		void pushBackLongHdf5ArrayOfValues(long * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, class AbstractHdfProxy * proxy, const long & nullValue, const long &  minimumValue, const long &  maximumValue);
		void pushBackLongHdf5ArrayOfValues(long * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, class AbstractHdfProxy * proxy, const long & nullValue);
	};
	
	class DiscretePropertySeries : public DiscreteProperty
	{
	public:
	};
	
	class CategoricalProperty : public AbstractValuesProperty
	{
	public:
		std::string getStringLookupUuid() const;
		StringTableLookup* getStringLookup();
		
		void pushBackLongHdf5Array1dOfValues(long * values, const unsigned int & valueCount, AbstractHdfProxy * proxy, const long & nullValue);
		void pushBackLongHdf5Array2dOfValues(long * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInSlowestDim, AbstractHdfProxy * proxy, const long & nullValue);
		void pushBackLongHdf5Array3dOfValues(long * values, const unsigned int & valueCountInFastestDim, const unsigned int & valueCountInMiddleDim, const unsigned int & valueCountInSlowestDim, AbstractHdfProxy * proxy, const long & nullValue);
		void pushBackLongHdf5ArrayOfValues(long * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, class AbstractHdfProxy * proxy, const long & nullValue);
	};
	
	class CategoricalPropertySeries : public CategoricalProperty
	{
	public:
	};
	
	class PropertyKindMapper
	{
	public:
		PropertyKindMapper(common::EpcDocument * epcDoc);

		std::string loadMappingFilesFromDirectory(const std::string & directory);
		std::string getApplicationPropertyKindNameFromResqmlStandardPropertyKindName(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & resqmlStandardPropertyKindName, const std::string & application) const;
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getResqmlStandardPropertyKindNameFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application) const;
		std::string getApplicationPropertyKindNameFromResqmlLocalPropertyKindUuid(const std::string & resqmlLocalPropertyKindUuid, const std::string & application) const;
		std::string getResqmlLocalPropertyKindUuidFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application) const;
		PropertyKind* addResqmlLocalPropertyKindToEpcDocumentFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application);
	};
}
