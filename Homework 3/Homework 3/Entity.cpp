//
//  Entity.cpp
//  Homework 3
//
//  Created by Steven Lee on 3/1/16.
//  Copyright © 2016 Steven Lee. All rights reserved.
//

#include "Entity.hpp"

void Entity::update(float& lastFrameTicks, float& elapsed, Matrix& projectionMatrix, Matrix& viewMatrix, ShaderProgram& program) {
    //    Update modelMatrix
    Matrix modelMatrix;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_A]) {
        if (x > -0.89) {
            x -= elapsed;
        }
    }
    else if(keys[SDL_SCANCODE_D]) {
        if (x < 0.89) {
            x += elapsed;
        }
    }
    modelMatrix.identity();
    modelMatrix.Translate(x, 0, 0);
    program.setModelMatrix(modelMatrix);
}

void Entity::render(ShaderProgram& program, GLuint textureID) {
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program.positionAttribute);
    glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program.texCoordAttribute);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Entity::setVertices(float arr[], size_t size) {
    if (size <= 12) {
        for (int i = 0; i < 12; i++) {
            vertices[i] = arr[i];
        }
    }
}

void Entity::setTexCoords(float arr[], size_t size) {
    if (size <= 12) {
        for (int i = 0; i < 12; i++) {
            texCoords[i] = arr[i];
        }
    }
}

void Entity::DrawText(ShaderProgram& program, int fontTexture, std::string text, float size, float spacing) {
    float texture_size = 1.0/16.0f;
    std::vector<float> vertexData;
    std::vector<float> texCoordData;
    for(int i=0; i < text.size(); i++) {
        float texture_x = (float)(((int)text[i]) % 16) / 16.0f;
        float texture_y = (float)(((int)text[i]) / 16) / 16.0f;
        vertexData.insert(vertexData.end(), {
            ((size+spacing) * i) + (-0.5f * size), 0.5f * size,
            ((size+spacing) * i) + (-0.5f * size), -0.5f * size,
            ((size+spacing) * i) + (0.5f * size), 0.5f * size,
            ((size+spacing) * i) + (0.5f * size), -0.5f * size,
            ((size+spacing) * i) + (0.5f * size), 0.5f * size,
            ((size+spacing) * i) + (-0.5f * size), -0.5f * size,
        });
        texCoordData.insert(texCoordData.end(), {
            texture_x, texture_y,
            texture_x, texture_y + texture_size,
            texture_x + texture_size, texture_y,
            texture_x + texture_size, texture_y + texture_size,
            texture_x + texture_size, texture_y,
            texture_x, texture_y + texture_size,
        }); }
    modelMatrix.Translate(-0.23
                          , 0.9, 0);
    program.setModelMatrix(modelMatrix);
    glUseProgram(program.programID);
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertexData.data());
    glEnableVertexAttribArray(program.positionAttribute);
    glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoordData.data());
    glEnableVertexAttribArray(program.texCoordAttribute);
    glBindTexture(GL_TEXTURE_2D, fontTexture);
    glDrawArrays(GL_TRIANGLES, 0, text.size() * 6);
    glDisableVertexAttribArray(program.positionAttribute);
    glDisableVertexAttribArray(program.texCoordAttribute);
}