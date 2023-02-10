/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(imebraImplementationMacros__INCLUDED_)
#define imebraImplementationMacros__INCLUDED_

#define get_dicomhero_object_holder(Type) ((dicomhero::Type*)m_##Type)

#define get_other_dicomhero_object_holder(Object, Type) ((dicomhero::Type*)Object->m_##Type)

#define set_dicomhero_object_holder(Type, Value) m_##Type = Value

#define reset_dicomhero_object_holder(Type) m_##Type = nullptr

#define delete_dicomhero_object_holder(Type) delete get_dicomhero_object_holder(Type)

#define get_dicomhero_parameter(Type) ((dicomhero::Type*)parameter_##Type)



#endif // imebraImplementationMacros__INCLUDED_
