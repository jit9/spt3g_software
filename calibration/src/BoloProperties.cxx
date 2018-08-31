#include <pybindings.h>
#include <calibration/BoloProperties.h>
#include <container_pybindings.h>

template <class A> void BolometerProperties::serialize(A &ar, unsigned v)
{
	using namespace cereal;

	G3_CHECK_VERSION(v);

	ar & make_nvp("G3FrameObject", base_class<G3FrameObject>(this));
	ar & make_nvp("physical_name", physical_name);
	ar & make_nvp("x_offset", x_offset);
	ar & make_nvp("y_offset", y_offset);
	ar & make_nvp("band", band);
	ar & make_nvp("pol_angle", pol_angle);
	ar & make_nvp("pol_efficiency", pol_efficiency);

	if (v > 1) {
		ar & make_nvp("wafer_id", wafer_id);
	}

	if (v == 2) {
		std::string squid_id = "junk";
		ar & make_nvp("squid_id", squid_id);
	}
	
	if (v > 3) {
		ar & make_nvp("pixel_id", pixel_id);		
	}
	

}

std::string BolometerProperties::Description() const
{
	std::ostringstream s;
	s << "Physical " << physical_name << " at " << band/G3Units::GHz << " GHz";

	return s.str();
}

G3_SERIALIZABLE_CODE(BolometerProperties);
G3_SERIALIZABLE_CODE(BolometerPropertiesMap);

PYBINDINGS("calibration") {
	EXPORT_FRAMEOBJECT(BolometerProperties, init<>(), "Physical bolometer properties, such as detector angular offsets. Does not include tuning-dependent properties of the detectors.")
	    .def_readwrite("physical_name", &BolometerProperties::physical_name,
	       "Physical name of the detector (e.g. some polarization at some "
	       "particular pixel on the wafer)")
	    .def_readwrite("x_offset", &BolometerProperties::x_offset,
	       "Horizontal pointing offset relative to boresight in angular units.")
	    .def_readwrite("y_offset", &BolometerProperties::y_offset,
	       "Vertical pointing offset relative to boresight in angular units.")
	    .def_readwrite("band", &BolometerProperties::band,
	       "Center of detector observing band in frequency units")
	    .def_readwrite("pol_angle", &BolometerProperties::pol_angle,
	       "Polarization angle in angular units")
	    .def_readwrite("pol_efficiency", &BolometerProperties::pol_efficiency,
	       "Polarization efficiency (0-1)")

	    .def_readwrite("wafer_id", &BolometerProperties::wafer_id,
	       "Name of the name this detector is on")
	    .def_readwrite("pixel_id", &BolometerProperties::pixel_id,
	       "Name of the pixel of which this detector is a part")
	;

	register_g3map<BolometerPropertiesMap>("BolometerPropertiesMap",
	    "Container for bolometer properties for focal plane, mapping "
	    "logical bolometer IDs to their physical properties.");
}

