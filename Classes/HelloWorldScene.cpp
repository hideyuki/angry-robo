#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    // win size
    Size winSize = Director::getInstance()->getWinSize();
    
    // add gravity
    PhysicsWorld* world = scene->getPhysicsWorld();
    Vect gravity;
    gravity.setPoint(0, -150);
    world->setGravity(gravity);
    
    // background
    Sprite* background = Sprite::create("background2.png");
    float backgroundScale = winSize.height/background->getContentSize().height * 1.01;
    background->setScale(backgroundScale);
    background->setAnchorPoint(Vec2(0, 0));
    //background->setPosition(Point(winSize.width / 2 , floor->getContentSize().height / 2));
    layer->addChild(background);
    
    // ground
    Rect rect = Rect(0, 0, winSize.width, 20);
    auto ground = Sprite::create();
    ground->setTextureRect(rect);
    ground->setColor(Color3B::WHITE);
    ground->setPosition(Vec2(ground->getContentSize().width/2, ground->getContentSize().height/2));
    PhysicsBody* groundPb = PhysicsBody::createBox(ground->getContentSize());
    groundPb->setDynamic(false);
    ground->setPhysicsBody(groundPb);
    layer->addChild(ground);
    
    // robo
    Sprite* robot = Sprite::create("blue_robot.png");
    robot->setPosition(Point(winSize.width / 5 , winSize.height / 2));
    PhysicsBody* robotPb = PhysicsBody::createBox(robot->getContentSize());
    robot->setPhysicsBody(robotPb);
    robot->setTag(1);
    layer->addChild(robot);
    
    // touch
    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, layer);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, layer);
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    /*
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);*/
    
    return true;
}

Rect HelloWorld::getRect(Node* node)
{
    Point point = node->getPosition();
    int width = node->getContentSize().width;
    int height = node->getContentSize().height;
    return Rect(point.x - (width / 2), point.y - (height / 2), width, height);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    CCLOG("onTouchBegan");
    Sprite* robot = (Sprite*)this->getChildByTag(1);
    Rect robotRect = getRect(robot);
    touchPoint = touch->getLocation();
    return robotRect.containsPoint(touchPoint);
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    CCLOG("onTouchEnded");
    Sprite* robot = (Sprite*)this->getChildByTag(1);
    Point endPoint = touch->getLocation();
    Vect force = Vect(touchPoint.x - endPoint.x, touchPoint.y - endPoint.y) * 4;
    robot->getPhysicsBody()->applyImpulse(force);
}

