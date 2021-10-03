#include <iostream>
#include "DrawCallTest.h"
int main()
{
	DrawCallTest test;
	test.Execute();
	test.Finalize();
	return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {

	// �V�F�[�_�����܂��B
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// �t�@�C�����璸�_�V�F�[�_�̃R�[�h��ǂݍ��݂܂��B
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}

	// �t�@�C������t���O�����g�V�F�[�_��ǂݍ��݂܂��B
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// ���_�V�F�[�_���R���p�C�����܂��B
	printf("Compiling shader : %sn", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// ���_�V�F�[�_���`�F�b�N���܂��B
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength != 0) {
		std::vector<GLchar> VertexShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		fprintf(stdout, "%sn", &VertexShaderErrorMessage[0]);
	}

	// �t���O�����g�V�F�[�_���R���p�C�����܂��B
	printf("Compiling shader : %sn", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// �t���O�����g�V�F�[�_���`�F�b�N���܂��B
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength != 0) {
		std::vector<GLchar>  FragmentShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		fprintf(stdout, "%sn", &FragmentShaderErrorMessage[0]);
	}

	// �v���O�����������N���܂��B
	fprintf(stdout, "Linking programn");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// �v���O�������`�F�b�N���܂��B
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength != 0)
	{
		std::vector<GLchar>  ProgramErrorMessage(max(InfoLogLength, int(1)));
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%sn", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
int main2()
{
	if (!glfwInit())
	{
		fprintf(stderr, "GLFW�̏������Ɏ��s���܂����Bn");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x �A���`�G�C���A�X
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL3.3���g���܂��B
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS�p:�K�������K�v�ł͂���܂���B
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // �Â�OpenGL�͎g���܂���B

	// Window���J���AOpenGL�R���e�L�X�g�����܂�
	GLFWwindow* window; // (�\�[�X�R�[�h�ł͂��̕ϐ��̓O���[�o���ł��B)
	window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "GLFW�E�B���h�E�̃I�[�v���Ɏ��s���܂����B ����Intel��GPU�Ȃ��, 3.3�ɑΉ����Ă��܂���B�`���[�g���A���̃o�[�W����2.1�������Ă��������Bn");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // GLEW������������
	glewExperimental = true; // �R�A�v���t�@�C���ŕK�v�ƂȂ�܂��B
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "GLEW�̏������Ɏ��s���܂����Bn");
		return -1;
	}

	// ���ŃG�X�P�[�v�L�[���������̂𑨂���̂�ۏ؂��܂��B
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	// 3���_��\��3�̃x�N�g���̔z��
	static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};

	GLuint programID = LoadShaders(
		"E:\\MyProgram\\KIProject\\DrawCallTest\\DrawCallTest\\Shader\\default.vert",
		"E:\\MyProgram\\KIProject\\DrawCallTest\\DrawCallTest\\Shader\\default.frag");
	// ���ꂪ���_�o�b�t�@���w���������̂ƂȂ�܂��B
	GLuint vertexbuffer;

	// �o�b�t�@��1���Avertexbuffer�Ɍ���ID�����܂��B
	glCreateBuffers(1, &vertexbuffer);

	// ���̃R�}���h��'vertexbuffer'�o�b�t�@�ɂ��Ăł��B
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// ���_��OpenGL�ɓn���܂��B
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	do {
		glUseProgram(programID);
		// �ŏ��̑����o�b�t�@:���_
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // ����0:0�ɓ��ɗ��R�͂���܂���B�������A�V�F�[�_����layout�Ƃ��킹�Ȃ��Ƃ����܂���B
			3,                  // �T�C�Y
			GL_FLOAT,           // �^�C�v
			GL_FALSE,           // ���K��?
			0,                  // �X�g���C�h
			(void*)0            // �z��o�b�t�@�I�t�Z�b�g
		);

		// �O�p�`��`���܂�!
		glDrawArrays(GL_TRIANGLES, 0, 3); // ���_0����n�܂�܂��B���v3�̒��_�ł��B&rarr;1�̎O�p�`�ł��B

		glDisableVertexAttribArray(0);

		// �o�b�t�@���X���b�v����B
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // ESC�L�[�������ꂽ���E�B���h�E�����������`�F�b�N����B
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glDeleteBuffers(1, &vertexbuffer);
	return 0;

}
