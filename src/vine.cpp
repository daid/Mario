#include "vine.h"

#include <sp2/graphics/textureManager.h>
#include <sp2/graphics/meshdata.h>

Vine::Vine(sp::P<sp::Node> parent)
: sp::Node(parent)
{
    render_data.type = sp::RenderData::Type::Normal;
    render_data.shader = sp::Shader::get("internal:basic.shader");
    render_data.texture = sp::texture_manager.get("items.png");
    render_data.order = -1;

    size = 0.0;
}

void Vine::onFixedUpdate()
{
    if (getPosition2D().y + size / 2 < 12)
    {
        size += 0.1;
        setPosition(getPosition2D() + sp::Vector2d(0, 0.05));
    }
    render_data.mesh = sp::MeshData::createQuad(sp::Vector2f(1, size), sp::Vector2f(15.0/16.0, 0), sp::Vector2f(16.0/16.0, size/16.0));
}
