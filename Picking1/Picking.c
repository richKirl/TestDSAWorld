#include "Picking.h"

void initFBORBO(Picking1 *p,int w,int h)
{
    LoadSetShaders(&p->shader,pathPickingVert,pathPickingFrag);
    // glGenFramebuffers(1, &p->FBO);
    // glBindFramebuffer(GL_FRAMEBUFFER,p->FBO);

    // // GL_RGBA8, width, height
    // glGenRenderbuffers(1,&p->cRBO);
    // glBindRenderbuffer(GL_RENDERBUFFER, p->cRBO);
    // glRenderbufferStorage(GL_RENDERBUFFER,GL_RGB8,w,h);
    // glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_RENDERBUFFER,p->cRBO);
    // //GL_DEPTH_COMPONENT24, width, height
    // glGenRenderbuffers(1,&p->dRBO);
    // glBindRenderbuffer(GL_RENDERBUFFER, p->dRBO);
    // glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT24,w,h);
    // glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,p->dRBO);
    // if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    //     printf("framebuffer error\n");
// create a 4x MSAA renderbuffer object for colorbuffer
// int msaa = 4;
// GLuint rboColorId;
glGenRenderbuffers(1, &p->cRBO);
glBindRenderbuffer(GL_RENDERBUFFER, p->cRBO);
glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, w, h);

// create a 4x MSAA renderbuffer object for depthbuffer
// GLuint rboDepthId;
glGenRenderbuffers(1, &p->dRBO);
glBindRenderbuffer(GL_RENDERBUFFER, p->dRBO);
//GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height
glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);

// create a 4x MSAA framebuffer object
// GLuint fboMsaaId;
glGenFramebuffers(1, &p->FBO);
glBindFramebuffer(GL_FRAMEBUFFER, p->FBO);

// attach colorbuffer image to FBO
//GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer
glFramebufferRenderbuffer(GL_FRAMEBUFFER,       // 1. fbo target: GL_FRAMEBUFFER
                          GL_COLOR_ATTACHMENT0, // 2. color attachment point
                          GL_RENDERBUFFER,      // 3. rbo target: GL_RENDERBUFFER
                          p->cRBO);          // 4. rbo ID

// attach depthbuffer image to FBO
glFramebufferRenderbuffer(GL_FRAMEBUFFER,       // 1. fbo target: GL_FRAMEBUFFER
                          GL_DEPTH_COMPONENT24,  // 2. depth attachment point
                          GL_RENDERBUFFER,      // 3. rbo target: GL_RENDERBUFFER
                          p->dRBO);          // 4. rbo ID

// check FBO status
GLenum status = glCheckNamedFramebufferStatus(p->FBO,GL_FRAMEBUFFER);
if(status != GL_FRAMEBUFFER_COMPLETE)
    printf("framebuffer error\n");
    // p->FBO = false;
glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void bindFBO(Picking1 *p)
{
    glBindFramebuffer(GL_FRAMEBUFFER, p->FBO);
}

void bindAsReadBindAsDrawBlit(Picking1 *p,int w,int h)//copycolor
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, p->FBO);//(GL_READ_FRAMEBUFFER, p->FBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, w, h, 0, 0, w, h, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void RenderColorFBO(Picking1 *p,mat4 m,mat4 m1,mat4 *proj,mat4 *view)
{
    // useSh(&p->shader);
    // SetUniformMat4(proj, p->shader.shaderProgram, "proj");
    // SetUniformMat4(&view[0], p->shader.shaderProgram, "view");
    // SetUniformMat4(&m, p->shader.shaderProgram, "model");
    // vec4 o1=(vec4){0.6,0.6,0.6,1.0};
    // vec4 o2=(vec4){0.6,0.6,0.6,1.0};
    // SetUniformVec4(&o1, p->shader.shaderProgram, "col");
    // SetUniformMat4(proj, p->shader.shaderProgram, "proj");
    // SetUniformMat4(&view[0], p->shader.shaderProgram, "view");
    // SetUniformMat4(&m1, p->shader.shaderProgram, "model");
    // SetUniformVec4(&o2, p->shader.shaderProgram, "col");
}

void bbrd(Picking1 *p)
{
    glNamedFramebufferReadBuffer(GL_FRAMEBUFFER, p->FBO);
    glNamedFramebufferDrawBuffer(GL_FRAMEBUFFER, p->FBO);
}

void delbrd(Picking1 *p)
{
    glDeleteFramebuffers(1,&p->FBO);
    glDeleteRenderbuffers(1,&p->cRBO);
    glDeleteRenderbuffers(1,&p->dRBO);
    delSh(&p->shader);
}