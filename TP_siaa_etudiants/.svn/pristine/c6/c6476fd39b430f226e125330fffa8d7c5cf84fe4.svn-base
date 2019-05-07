#ifndef _HelperGl_Shader_H
#define _HelperGl_Shader_H

#include <GL/glew.h>
#include <Math/Vectorf.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cassert>
#include <map>

namespace HelperGl
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Shader
	///
	/// \brief	Shader class containing a shader (vertex or fragment) source code that can be compiled.
	/// 		This class also offers facilities for shader loading / writing.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	09/12/2015
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Shader
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \typedef	enum
		///
		/// \brief	Enumeration providing the type of the shader (fragment of vertex shader).
		////////////////////////////////////////////////////////////////////////////////////////////////////
		typedef enum {vertex = GL_VERTEX_SHADER, fragment = GL_FRAGMENT_SHADER} ShaderType ;

	protected:
		/// \brief	The source of the shader.
		::std::stringstream m_shader ;
		/// \brief	Type of the shader.
		ShaderType m_shaderType ;
		/// \brief	Identifier for the shader.
		GLuint m_shaderId ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	size_t Shader::streamSize()
		///
		/// \brief	Gets the stream size (number of characters in the source code of the shader).
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		size_t streamSize();

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Shader::Shader(ShaderType type)
		///
		/// \brief	Constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \param	type	The type of the shader (fragment of vertex).
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Shader(ShaderType type);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	ShaderType Shader::getType() const
		///
		/// \brief	Gets the type.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \return	The type.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		ShaderType getType() const
		{
			return m_shaderType ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	::std::ostream & Shader::getStream()
		///
		/// \brief	Returns the stream containing the source of the shader.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		////////////////////////////////////////////////////////////////////////////////////////////////////
		::std::ostream & getStream()
		{
			return m_shader ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	GLuint Shader::getId() const
		///
		/// \brief	Gets the identifier.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \return	The identifier.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		GLuint getId() const
		{
			return m_shaderId ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Shader::loadFromFile(const ::std::string & filename)
		///
		/// \brief	Loads the shader source from the provided file.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \param	filename	Filename of the file.
		///
		/// \return	true if it succeeds, false if it fails.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool loadFromFile(const ::std::string & filename);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Shader::compile()
		///
		/// \brief	Compiles this shader.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \return	true if it succeeds, false if it fails.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool compile();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Shader::isCompiled() const
		///
		/// \brief	Query if this object is compiled.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \return	true if compiled, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isCompiled() const
		{
			return m_shaderId!=0 ;
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	ShaderProgram
	///
	/// \brief	Shader program class.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	09/12/2015
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ShaderProgram
	{
	protected:
		/// \brief	The vertex shader.
		Shader * m_vertexShader ;
		/// \brief	The fragment shader.
		Shader * m_fragmentShader ;
		/// \brief	Identifier for the program.
		GLuint   m_programId ;

		::std::map<::std::string, GLint> m_attributes ;
		::std::map<::std::string, GLint> m_uniforms ;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	ShaderProgram::ShaderProgram(Shader * vertexShader=NULL, Shader * fragmentShader=NULL)
		///
		/// \brief	Constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \param	vertexShader  	(optional) [in,out] If non-null, the vertex shader.
		/// \param	fragmentShader	(optional) [in,out] If non-null, the fragment shader.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		ShaderProgram(Shader * vertexShader=NULL, Shader * fragmentShader=NULL)
			: m_vertexShader(vertexShader), m_fragmentShader(fragmentShader)
		{
			assert(m_vertexShader==NULL || m_vertexShader->getType()==Shader::vertex) ;
			assert(m_fragmentShader==NULL || m_fragmentShader->getType()==Shader::fragment) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void ShaderProgram::setVertexShader(Shader * shader)
		///
		/// \brief	Sets vertex shader.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \param [in,out]	shader	If non-null, the shader.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setVertexShader(Shader * shader)
		{
			assert(shader->getType()==Shader::vertex) ;
			m_vertexShader = shader ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void ShaderProgram::setFragmentShader(Shader * shader)
		///
		/// \brief	Sets fragment shader.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \param [in,out]	shader	If non-null, the shader.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setFragmentShader(Shader * shader)
		{
			assert(shader->getType()==Shader::fragment) ;
			m_fragmentShader = shader ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void ShaderProgram::setShader(Shader * shader)
		///
		/// \brief	Sets a shader.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \param [in,out]	shader	If non-null, the shader.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setShader(Shader * shader)
		{
			switch(shader->getType())
			{
			case Shader::vertex:
				m_vertexShader = shader ;
				break;
			case Shader::fragment:
				m_fragmentShader = shader ;
				break ;
			default:
				::std::cerr<<"ShaderProgram: wrong shader type"<<::std::endl ;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool ShaderProgram::compileAndLink()
		///
		/// \brief	Compiles dans links the shader program.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \return	true if it succeeds, false if it fails.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool compileAndLink();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	GLuint ShaderProgram::getId() const
		///
		/// \brief	Gets the identifier.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \return	The identifier.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		GLuint getId() const
		{
			return m_programId ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool ShaderProgram::isLinked() const
		///
		/// \brief	Query if this object is linked.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \return	true if linked, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isLinked() const
		{
			return m_programId!=0 ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void ShaderProgram::enable()
		///
		/// \brief	Enables this shader.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void enable()
		{
			assert(isLinked()) ;
			glUseProgram(m_programId) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void ShaderProgram::disable()
		///
		/// \brief	Disables this shader.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void disable()
		{
			glUseProgram(0) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	GLint ShaderProgram::getAttributeLocation(const ::std::string & name)
		///
		/// \brief	Gets an attribute location.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \param	name	The name of the attribute.
		///
		/// \return	The attribute location.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		GLint getAttributeLocation(const ::std::string & name);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	GLuint ShaderProgram::getUniformLocation(const ::std::string & name)
		///
		/// \brief	Gets a uniform location.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/02/2016
		///
		/// \param	name	The name of the uniform.
		///
		/// \return	The uniform location.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		GLuint getUniformLocation(const ::std::string & name);
	};
}

#endif