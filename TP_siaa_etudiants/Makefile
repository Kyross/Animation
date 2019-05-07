CC = g++
CC_OPT = -std=c++11 -O3
CC_INC = -I./src
LD_LIB = -lGLEW -lGLU -lGL -l3ds -lglut -lSOIL -ltbb
OUTPUT_DIR = ./bin/Release
PROG = $(OUTPUT_DIR)/TP_IMA
OBJ= $(OUTPUT_DIR)/VBO.o $(OUTPUT_DIR)/Buffer.o $(OUTPUT_DIR)/Loader3ds.o $(OUTPUT_DIR)/shader.o $(OUTPUT_DIR)/Text.o $(OUTPUT_DIR)/Mesh.o $(OUTPUT_DIR)/PhongShader.o $(OUTPUT_DIR)/TextureServer.o $(OUTPUT_DIR)/Draw.o $(OUTPUT_DIR)/KinematicChain.o $(OUTPUT_DIR)/SpringMassSystem.o $(OUTPUT_DIR)/Path.o $(OUTPUT_DIR)/main_application.o $(OUTPUT_DIR)/Base.o $(OUTPUT_DIR)/Menu.o $(OUTPUT_DIR)/ApplicationSelection.o $(OUTPUT_DIR)/Patch.o $(OUTPUT_DIR)/ParticleSystemNode.o $(OUTPUT_DIR)/MeshVBO_v2.o

$(PROG): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LD_LIB)
	ln -f -s $(PROG) .

clean:
	rm $(OBJ)
	rm $(PROG)

$(OUTPUT_DIR)/VBO.o: src/HelperGl/src/VBO.cpp src/HelperGl/VBO.h src/Math/Vectorf.h \
 src/Math/Vector.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/Buffer.o: src/HelperGl/src/Buffer.cpp src/HelperGl/Buffer.h \
 src/Math/Vectorf.h src/Math/Vector.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/Loader3ds.o: src/HelperGl/src/Loader3ds.cpp src/HelperGl/Loader3ds.h \
 src/Config.h src/System/Path.h src/Math/Vectorf.h src/Math/Vector.h \
 src/HelperGl/Mesh.h src/HelperGl/Material.h src/HelperGl/Color.h \
 src/HelperGl/TextureServer.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/shader.o: src/HelperGl/src/shader.cpp src/HelperGl/Shader.h \
 src/Math/Vectorf.h src/Math/Vector.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/Text.o: src/HelperGl/src/Text.cpp src/HelperGl/Text.h \
 src/HelperGl/Color.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/Mesh.o: src/HelperGl/src/Mesh.cpp src/HelperGl/Mesh.h src/Math/Vectorf.h \
 src/Math/Vector.h src/HelperGl/Material.h src/HelperGl/Color.h \
 src/HelperGl/TextureServer.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/PhongShader.o: src/HelperGl/src/PhongShader.cpp \
 src/HelperGl/PhongShader.h src/HelperGl/Shader.h src/Math/Vectorf.h \
 src/Math/Vector.h src/Config.h src/System/Path.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/TextureServer.o: src/HelperGl/src/TextureServer.cpp \
 src/HelperGl/TextureServer.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/Draw.o: src/HelperGl/src/Draw.cpp src/HelperGl/Draw.h \
 src/HelperGl/Material.h src/HelperGl/Color.h \
 src/HelperGl/TextureServer.h src/HelperGl/Mesh.h src/Math/Vectorf.h \
 src/Math/Vector.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/KinematicChain.o: src/Animation/src/KinematicChain.cpp \
 src/Animation/KinematicChain.h src/Math/Matrix4x4f.h \
 src/Math/Matrix4x4.h src/Math/Vector.h src/Math/Vectorf.h \
 src/Math/Interval.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/SpringMassSystem.o: src/Animation/src/SpringMassSystem.cpp \
 src/Animation/SpringMassSystem.h src/Math/Vectorf.h src/Math/Vector.h \
 src/Math/Matrix4x4f.h src/Math/Matrix4x4.h src/Math/Interval.h \
 src/Utils/History.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/Path.o: src/System/src/Path.cpp src/System/Path.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/main_application.o: src/main_application.cpp \
 src/Application/ApplicationSelection.h src/Application/Base.h \
 src/Config.h src/System/Path.h src/Application/Menu.h \
 src/GL/compatibility.h src/Math/Matrix4x4f.h src/Math/Matrix4x4.h \
 src/Math/Vector.h src/Math/Vectorf.h src/Math/Constant.h \
 src/Application/TP1.h src/HelperGl/Mesh.h src/HelperGl/Material.h \
 src/HelperGl/Color.h src/HelperGl/TextureServer.h \
 src/HelperGl/Loader3ds.h src/HelperGl/Draw.h src/HelperGl/LightServer.h \
 src/HelperGl/PhongShader.h src/HelperGl/Shader.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/Base.o: src/Application/src/Base.cpp src/Application/Base.h src/Config.h \
 src/System/Path.h src/Application/Menu.h src/GL/compatibility.h \
 src/Math/Matrix4x4f.h src/Math/Matrix4x4.h src/Math/Vector.h \
 src/Math/Vectorf.h src/Math/Constant.h src/HelperGl/Text.h \
 src/HelperGl/Color.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/Menu.o: src/Application/src/Menu.cpp src/Application/Menu.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/ApplicationSelection.o: src/Application/src/ApplicationSelection.cpp \
 src/Application/ApplicationSelection.h src/Application/Base.h \
 src/Config.h src/System/Path.h src/Application/Menu.h \
 src/GL/compatibility.h src/Math/Matrix4x4f.h src/Math/Matrix4x4.h \
 src/Math/Vector.h src/Math/Vectorf.h src/Math/Constant.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/Patch.o: src/SceneGraph/src/Patch.cpp src/SceneGraph/Patch.h \
 src/SceneGraph/NodeInterface.h src/HelperGl/Material.h \
 src/HelperGl/Color.h src/HelperGl/TextureServer.h src/HelperGl/Buffer.h \
 src/Math/Vectorf.h src/Math/Vector.h src/HelperGl/PhongShader.h \
 src/HelperGl/Shader.h src/HelperGl/LightServer.h src/HelperGl/Draw.h \
 src/HelperGl/Mesh.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/ParticleSystemNode.o: src/SceneGraph/src/ParticleSystemNode.cpp \
 src/SceneGraph/ParticleSystemNode.h src/SceneGraph/PointRenderer.h \
 src/SceneGraph/NodeInterface.h src/HelperGl/Buffer.h src/Math/Vectorf.h \
 src/Math/Vector.h src/HelperGl/Color.h src/Animation/ParticleSystem.h \
 src/Animation/Particle.h src/Math/Sampler.h src/Math/Quaternion.h \
 src/Math/Interval.h src/Math/Interpolation.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

$(OUTPUT_DIR)/MeshVBO_v2.o: src/SceneGraph/src/MeshVBO_v2.cpp \
 src/SceneGraph/MeshVBO_v2.h src/SceneGraph/NodeInterface.h \
 src/HelperGl/Mesh.h src/Math/Vectorf.h src/Math/Vector.h \
 src/HelperGl/Material.h src/HelperGl/Color.h \
 src/HelperGl/TextureServer.h src/HelperGl/VBO.h \
 src/HelperGl/PhongShader.h src/HelperGl/Shader.h \
 src/HelperGl/LightServer.h src/HelperGl/Draw.h
	$(CC) -c $(CC_OPT) $(CC_INC) -o $@ $<

