#include "player.h"
#include "movementstate.h"

// Initializer functions

void Player::initVariables()
{
    attacking = false;
}

void Player::initComponents()
{
}

// Constructors / Destructors

Player::Player(float x, float y, sf::Texture &textureSheet)
{
    initVariables();

    setPosition(x, y);

    createMovementComponent(200.f, 1500.f, 900.f);
    createAnimationComponent(textureSheet);
    createHitboxComponent(sprite, 10.f, 5.f, 44.f, 54.f);
    createAttributeComponent(1);

    animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
    animationComponent->addAnimation("WALK_DOWN", 12.f, 0, 1, 3, 0, 64, 64);
    animationComponent->addAnimation("WALK_LEFT", 12.f, 4, 1, 3, 0, 64, 64);
    animationComponent->addAnimation("WALK_RIGHT", 12.f, 8, 1, 3, 0, 64, 64);
    animationComponent->addAnimation("WALK_UP", 12.f, 12, 1, 3, 0, 64, 64);
    animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 13, 0, 64, 64);
}

Player::~Player()
{

}

Component_Attribute *Player::getAttributeComponent()
{
    return attributeComponent;
}

// Functions

void Player::loseHP(int hp)
{
    attributeComponent->hp -= hp;

    if (attributeComponent->hp < 0) {
        attributeComponent->hp = 0;
    }
}

void Player::gainHP(int hp)
{
    attributeComponent->hp += hp;

    if (attributeComponent->hp > attributeComponent->hpMax) {
        attributeComponent->hp = attributeComponent->hpMax;
    }
}

void Player::loseEXP(int exp)
{
    attributeComponent->exp += exp;

    if (attributeComponent->exp < 0) {
        attributeComponent->exp = 0;
    }
}

void Player::gainEXP(int exp)
{
    attributeComponent->gainExp(exp);
}

void Player::updateAttack()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        //attacking = true;
    }
}

void Player::updateAnimation(const float &dt)
{
    if (attacking) {
        // Set origin depending on direction
        if (sprite.getScale().x > 0.f) {
            sprite.setOrigin(96.f, 0.f);
        }
        else {
            sprite.setOrigin(258.f + 96.f, 0.f);
        }

        if (animationComponent->play("ATTACK", dt, true)) { // When animation is done
            attacking = false;

            if (sprite.getScale().x > 0.f) {
                sprite.setOrigin(0.f, 0.f);
            }
            else {
                sprite.setOrigin(258.f, 0.f);
            }
        }
    }
    if (movementComponent->getState(MovementState::IDLE)) {
        animationComponent->play("IDLE", dt);
    }
    else if (movementComponent->getState(MovementState::MOVING_LEFT)){
        animationComponent->play("WALK_LEFT", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
    }
    else if (movementComponent->getState(MovementState::MOVING_RIGHT)) {
        animationComponent->play("WALK_RIGHT", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
    }
    else if (movementComponent->getState(MovementState::MOVING_UP)) {
        animationComponent->play("WALK_UP", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
    }
    else if (movementComponent->getState(MovementState::MOVING_DOWN)) {
        animationComponent->play("WALK_DOWN", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
    }
}


void Player::update(const float &dt)
{
    attributeComponent->update();
    movementComponent->update(dt);
    updateAttack();
    updateAnimation(dt);
    hitboxComponent->update();
}

void Player::render(sf::RenderTarget &target, sf::Shader *shader, bool showHitBox)
{
    if (shader) {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", getCenter());

        target.draw(sprite, shader);
    }
    else {
        target.draw(sprite);
    }

    if (showHitBox) {
        hitboxComponent->render(target);
    }
}
