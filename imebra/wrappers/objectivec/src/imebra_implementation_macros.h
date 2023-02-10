/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraImplementationMacros__INCLUDED_)
#define imebraImplementationMacros__INCLUDED_

#define get_imebra_object_holder(Type) ((imebra::Type*)m_##Type)

#define get_other_imebra_object_holder(Object, Type) ((imebra::Type*)Object->m_##Type)

#define set_imebra_object_holder(Type, Value) m_##Type = Value

#define reset_imebra_object_holder(Type) m_##Type = nullptr

#define delete_imebra_object_holder(Type) delete get_imebra_object_holder(Type)

#define get_imebra_parameter(Type) ((imebra::Type*)parameter_##Type)



#endif // imebraImplementationMacros__INCLUDED_
