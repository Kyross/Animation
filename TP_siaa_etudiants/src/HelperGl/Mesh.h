#ifndef _HelperGl_Mesh_H
#define _HelperGl_Mesh_H

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <Math/Vectorf.h>
#include <HelperGl/Material.h>

namespace HelperGl
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Mesh
	///
	/// \brief	A mesh composed of triangular faces.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	06/12/2015
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Mesh
	{
	public:
		struct Face
		{
			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \property	unsigned int m_verticesIndexes[3]
			///
			/// \brief	The vertices indexes[ 3].
			////////////////////////////////////////////////////////////////////////////////////////////////////
			unsigned int m_verticesIndexes[3] ;

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \property	unsigned int m_textureIndexes[3]
			///
			/// \brief	The texture coordinates indexes[ 3].
			///
			/// \return	The m texture indexes[ 3].
			////////////////////////////////////////////////////////////////////////////////////////////////////
			unsigned int m_textureIndexes[3] ;
		
			/// \brief	The normal.
			Math::Vector3f m_normal ;

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// \fn	Face()
			///
			/// \brief	Default constructor.
			///
			/// \author	F. Lamarche, Université de Rennes 1
			/// \date	03/02/2016
			////////////////////////////////////////////////////////////////////////////////////////////////////
			Face()
			{
				::std::fill(m_verticesIndexes, m_verticesIndexes+3, 0) ;
				::std::fill(m_textureIndexes, m_textureIndexes+3, 0) ;
			}
		};

	private:
		/// \brief	The name.
		::std::string m_name ;
		/// \brief	The vertices.
		::std::vector<Math::Vector3f> m_vertices ;
		/// \brief	The vertices normals.
		::std::vector<Math::Vector3f> m_verticesNormals ;
		/// \brief	The texture coordinates.
		::std::vector<Math::Vector2f> m_textureCoordinates ;
		/// \brief	The faces.
		::std::vector<Face> m_faces ;
		/// \brief	The material.
		Material * m_material ;	

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Mesh::Mesh()
		///
		/// \brief	Default constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Mesh()
		{}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Mesh::setName(const ::std::string & name)
		///
		/// \brief	Sets the name of the mesh.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \param	name	The name.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setName(const ::std::string & name)
		{
			m_name = name ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Mesh::setVertices(const ::std::vector<Math::Vector3f> & vertices)
		///
		/// \brief	Sets the vertices of the mesh.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \param	vertices	The vertices.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setVertices(const ::std::vector<Math::Vector3f> & vertices)
		{
			m_vertices = vertices ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Mesh::setTextureCoordinates(const ::std::vector<Math::Vector2f> & textureCoordinates)
		///
		/// \brief	Sets the texture coordinates of the mesh.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \param	textureCoordinates	The texture coordinates.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setTextureCoordinates(const ::std::vector<Math::Vector2f> & textureCoordinates)
		{
			m_textureCoordinates = textureCoordinates;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Mesh::hasTextureCoordinates() const
		///
		/// \brief	Query if this object has texture coordinates.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \return	true if texture coordinates, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool hasTextureCoordinates() const
		{
			return m_textureCoordinates.size()>0 ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Mesh::setMaterial(Material * material)
		///
		/// \brief	Sets the material associated with the mesh.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \param [in,out]	material	If non-null, the material.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setMaterial(Material * material)
		{
			m_material = material ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Mesh::setFaces(const ::std::vector<Face> & faces)
		///
		/// \brief	Sets the faces.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \param	faces	The faces.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setFaces(const ::std::vector<Face> & faces)
		{
			m_faces = faces ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const std::string & Mesh::getName() const
		///
		/// \brief	Gets the name.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \return	The name.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const std::string & getName() const
		{
			return m_name ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const ::std::vector<Math::Vector3f> & Mesh::getVertices() const
		///
		/// \brief	Gets the vertices.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \return	The vertices.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const ::std::vector<Math::Vector3f> & getVertices() const
		{
			return m_vertices ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const ::std::vector<Math::Vector2f> & Mesh::getTextureCoordinates() const
		///
		/// \brief	Gets the texture coordinates.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \return	The texture coordinates.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const ::std::vector<Math::Vector2f> & getTextureCoordinates() const
		{
			return m_textureCoordinates ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const ::std::vector<Face> & Mesh::getFaces() const
		///
		/// \brief	Gets the faces of the mesh.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \return	The faces.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const ::std::vector<Face> & getFaces() const 
		{
			return m_faces ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const Material * Mesh::getMaterial() const
		///
		/// \brief	Gets the material.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \return	null if it fails, else the material.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Material * getMaterial() const
		{
			return m_material ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Mesh::setVerticesNormals(const ::std::vector<Math::Vector3f> & normals)
		///
		/// \brief	Sets vertices normals.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \param	normals	The normals.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setVerticesNormals(const ::std::vector<Math::Vector3f> & normals)
		{
			m_verticesNormals = normals ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const ::std::vector<Math::Vector3f> & Mesh::getVerticesNormals() const
		///
		/// \brief	Gets vertices normals.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \return	The vertices normals.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const ::std::vector<Math::Vector3f> & getVerticesNormals() const
		{
			return m_verticesNormals ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Mesh::hasVerticesNormals() const
		///
		/// \brief	Query if this object has vertices normals.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \return	true if vertices normals, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool hasVerticesNormals() const
		{
			return m_verticesNormals.size()!=0 ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector3f Mesh::computeFaceNormal(const Face & face)
		///
		/// \brief	Calculates the face normal.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \param	face	The face.
		///
		/// \return	The calculated face normal.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector3f computeFaceNormal(const Face & face)
		{
			const Math::Vector3f & v0= m_vertices[face.m_verticesIndexes[0]] ;
			const Math::Vector3f & v1= m_vertices[face.m_verticesIndexes[1]] ;
			const Math::Vector3f & v2= m_vertices[face.m_verticesIndexes[2]] ;
			return (v1-v0)^(v2-v0) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector3f Mesh::computeFaceNormal(size_t index)
		///
		/// \brief	Calculates the face normal.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \param	index	Zero-based index of the.
		///
		/// \return	The calculated face normal.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector3f computeFaceNormal(size_t index)
		{
			return computeFaceNormal(m_faces[index]) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Mesh::computeFacesNormals()
		///
		/// \brief	Calculates the faces normals.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	06/12/2015
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void computeFacesNormals()
		{
			for(auto it=m_faces.begin() ; it!=m_faces.end() ; ++it)
			{
				Face & face = *it ;
				face.m_normal = computeFaceNormal(face) ;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Mesh::computeVertexNormal()
		///
		/// \brief	Calculates a per vertex normal. This function assumes that a normal
		/// 		has been computed for each face. If its not the case, please, call
		/// 		computeFacesNormals before calling this method.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	06/12/2015
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void computeVertexNormal() ;


		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Mesh::clean()
		///
		/// \brief	Cleans the 3D model by removing unused vertices.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	30/11/2015
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void clean() ;
	};
}

#endif