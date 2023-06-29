#include "glad/glad.h"
#include "GLFW/glfw3.h"

//Para usar texturas
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
//

//
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
//

#include <iostream>

void redimensionarVentana(GLFWwindow *, int, int);
void teclaPresionada(GLFWwindow* window)
{
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

	 if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS){
     std::cout << "Tecla 0 Presioanda\n";
   }
}


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "out vec2 TexCoord;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
    "   TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
    "}\n\0";
 
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec2 TexCoord;\n"   
    "uniform sampler2D ourTexture;\n"
    "void main()\n"
    "{\n"
    "   FragColor = texture(ourTexture, TexCoord);\n"
    "}\n\0";

/////
GLuint transformLoc;

int main(){
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creación de la Ventana
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);  
    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, redimensionarVentana);

    // Carga de de apuntadores a funciones OpenGL 
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    /////////////////////
    // Dimensiones del "viewport"
    glViewport( 0, 0, screenWidth, screenHeight );
    
    // Profundidad de Buffer
    glEnable( GL_DEPTH_TEST );
    
    // enable alpha support
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    /////////////////////////////SHADERS//////////////////////////////
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Enlazar
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    //Eliminación de Shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Todas las caras de un Cubo!
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    ///2. Creando objetos VBO, VAO e IBO 
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Enlazar VAO y VBO
    // y configurar los atributos de vértices
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    ///Atributo Posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0); 
    glEnableVertexAttribArray(0);

    ///Atributo Coordenada de Textura
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float))); 
    glEnableVertexAttribArray(2);
    ///////////////////////////////////////////////////

    /*Cargando Imagen para Textura
    La función stbi_load primero toma como entrada la ubicación de un archivo 
    de imagen. Luego espera que proporcione tres enteros como su segundo, 
    tercer y cuarto argumento que stb_image.h llenará con el ancho, alto y 
    número de canales de color de la imagen resultante.
    */
    int ancho, alto, canales;
    unsigned char *img = stbi_load("./imagenes/wall.jpg", &ancho, &alto, &canales, 0);


    ///Textura
    /*
      La función glGenTextures primero toma como entrada cuántas texturas 
      se quieren generar y las almacena en un arreglo de enteros 
      (segundo argumento - en nuestro caso, solo un único entero). 
    */
    unsigned int textura;
    glGenTextures(1, &textura);  

    /*
      Se requeire vincular la textura, al igual que otros objetos, para 
      que cualquier comando de textura posterior configure la textura 
      actualmente vinculada
    */
    glBindTexture(GL_TEXTURE_2D, textura);  

    /* 
      Establecer las opciones de ajuste/filtrado de texturas 
      (en el objeto de textura enlazado actualmente)
    */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /*
      Ahora que la textura está enlazada, podemos generar una textura 
      utilizando los datos de imagen previamente cargados. 
      Las texturas se generan con glTexImage2D
    */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    glGenerateMipmap(GL_TEXTURE_2D);

    /*
     glTextImage tiene varios parámetros:
        - 1er: Se especifica el destino de la textura.
          GL_TEXTURE_2D <--> textura en el objeto de textura enlazado 
          actual en el mismo objetivo.
        - 2do: Se especifica el nivel de mipmap para crear una textura 
          si desea configurar cada nivel de mipmap manualmente - En este caso, 
          queda en nivel base (0).
        - 3ero: Tipo de formato a almacenar la textura. Nuestra imagen 
          solo tiene valores RGB, por lo que también almacenaremos la textura 
          con valores RGB.
        - 4to y 5to: Establecen el ancho y el alto de la textura resultante.
        - El siguiente argumento siempre debe ser 0 (algunas cosas heredadas).
        - 7mo y 8vo: Formato y tipo de datos de la imagen de origen.
    
    Una vez que se llama a glTexImage2D, el objeto de textura enlazado 
    actualmente tiene la imagen de textura adjunta. 
    Sin embargo, actualmente solo tiene cargado el nivel base de la imagen de 
    textura y si queremos usar mipmaps, debemos especificar todas las diferentes 
    imágenes manualmente (incrementando continuamente el segundo argumento) o 
    podemos llamar a glGenerateMipmap después de generar la textura. 
    Esto generará automáticamente todos los mipmaps necesarios para el texto enlazado 
    actualmente.
    */

    stbi_image_free(img);

    ////////////GLM
    glm::mat4 projection;
    projection = glm::perspective( 45.0f, ( GLfloat )screenWidth / ( GLfloat )screenHeight, 0.1f, 100.0f );
    ////////////

    transformLoc = glGetUniformLocation(shaderProgram, "transform");
    
    // render loop
    while (!glfwWindowShouldClose(window)){
        glfwPollEvents();
        teclaPresionada(window);
        

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // Limpieza de Color y Profundidad de Buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //////Textura
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, textura );
        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1" ), 0 );
        //

        glUseProgram(shaderProgram);
       
        /////////////////////////////
        glm::mat4 model = glm::mat4( 1.0f );
        glm::mat4 view = glm::mat4( 1.0f );
        model = glm::rotate( model, ( GLfloat)glfwGetTime( ) * 1.0f, glm::vec3( 0.5f, 1.0f, 0.0f ) ); // use with perspective projection

        view = glm::translate( view, glm::vec3( 0.0f, 0.0f, -3.0f ) ); // use with perspective projection
        
        // Get their uniform location
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model" );
        GLint viewLoc = glGetUniformLocation(shaderProgram, "view" );
        GLint projLoc = glGetUniformLocation(shaderProgram, "projection" );

        // Pass them to the shaders
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ) );
        
        // Draw container
        glBindVertexArray( VAO );
        glDrawArrays( GL_TRIANGLES, 0, 36 );
        glBindVertexArray( 0 );
        
        // Swap the screen buffers
        glfwSwapBuffers( window );    
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void redimensionarVentana(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}
