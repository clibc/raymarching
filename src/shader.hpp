#ifndef H_SHADER
#define H_SHADER

char *_load_file(const char *filepath);

GLuint create_shader(const char *vpath, const char *fpath)
{
    char *vsource = _load_file(vpath);
    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, (const char **)&vsource, NULL);
    glCompileShader(vshader);

    GLint success = 0;
    glGetShaderiv(vshader, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE)
    {
        GLint logSize = 0;
        glGetShaderiv(vshader, GL_INFO_LOG_LENGTH, &logSize);
        GLchar *error_message = (GLchar *)malloc(sizeof(GLchar) * logSize);
        glGetShaderInfoLog(vshader, logSize, &logSize, &error_message[0]);
        glDeleteShader(vshader);
        printf("Error in %s: %s\n", vpath, error_message);
        exit(1);
    }

    char *fsource = _load_file(fpath);
    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, (const char **)&fsource, NULL);
    glCompileShader(fshader);

    glGetShaderiv(fshader, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE)
    {
        GLint logSize = 0;
        glGetShaderiv(fshader, GL_INFO_LOG_LENGTH, &logSize);
        GLchar *error_message = (GLchar *)malloc(sizeof(GLchar) * logSize);
        glGetShaderInfoLog(fshader, logSize, &logSize, &error_message[0]);
        printf("Error in %s:  %s\n", fpath, error_message);
        glDeleteShader(vshader);
        exit(1);
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vshader);
    glAttachShader(program, fshader);

    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);

    if (isLinked == GL_FALSE)
    {
        GLint logSize = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
        GLchar *error_message = (GLchar *)malloc(sizeof(GLchar) * logSize);
        glGetProgramInfoLog(program, logSize, &logSize, error_message);
        printf("%s", error_message);
        glDeleteProgram(program);
        glDeleteShader(vshader);
        glDeleteShader(fshader);
        exit(1);
    }

    glDetachShader(program, vshader);
    glDetachShader(program, fshader);

    free(vsource);
    free(fsource);
    return program;
}

char *_load_file(const char *filepath)
{
    char *buffer;
    int size = 0;
    FILE *file = fopen(filepath, "rb");

    if (file)
    {
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        rewind(file);
        buffer = (char *)malloc((sizeof(char) * size) + (sizeof(char) * 1));
        fread(buffer, sizeof(char), size, file);
        buffer[size] = '\0';
    }
    else
    {
        printf("File is not found: %s\n", filepath);
        exit(1);
    }

    fclose(file);
    return buffer;
}

#endif//H_SHADER
