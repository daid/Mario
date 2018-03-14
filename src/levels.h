void createFinish(sp::P<sp::Scene> scene);
void createArea1_2a(sp::P<sp::Scene> scene);
void createArea2_2a(sp::P<sp::Scene> scene);
void createArea4_2a(sp::P<sp::Scene> scene);
void createArea7_2a(sp::P<sp::Scene> scene);
void createArea1_1(sp::P<sp::Scene> scene)
{
    //complement=0 index=25
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Mountain);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.nextPage(); //0
    
    level.questionBlock(0, 12 - 7);
    level.horizontalBricks(4, 12 - 7, 5);
    level.questionBlock(5, 12 - 7, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.questionBlock(6, 12 - 3);
    level.questionBlock(7, 12 - 7);
    level.pipe(12, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.nextPage(); //1
    
    level.pipe(6, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.pipe(14, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.nextPage(); //2
    
    level.pipe(9, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    //enter pipe(9, 12 - 7);
    level.nextPage(); //3
    
    level.questionBlock(0, 12 - 6, QuestionBlock::Type::Hidden, QuestionBlock::Contents::Life);
    level.hole(5, 2);
    level.horizontalBricks(13, 12 - 7, 3);
    level.questionBlock(14, 12 - 7, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.nextPage(); //4
    
    level.horizontalBricks(0, 12 - 3, 8);
    level.hole(6, 3);
    level.horizontalBricks(11, 12 - 3, 3);
    level.questionBlock(14, 12 - 3);
    level.questionBlock(14, 12 - 7, QuestionBlock::Type::Brick, QuestionBlock::Contents::MultiCoin);
    level.nextPage(); //5
    
    level.horizontalBricks(4, 12 - 7, 1);
    level.questionBlock(5, 12 - 7, QuestionBlock::Type::Brick, QuestionBlock::Contents::Star);
    level.questionBlock(10, 12 - 7);
    level.questionBlock(13, 12 - 3, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.questionBlock(13, 12 - 7);
    level.nextPage(); //6
    
    level.questionBlock(0, 12 - 7);
    level.horizontalBricks(6, 12 - 7, 1);
    level.horizontalBricks(9, 12 - 3, 3);
    level.nextPage(); //7
    
    level.horizontalBricks(0, 12 - 3, 4);
    level.questionBlock(1, 12 - 3);
    level.questionBlock(2, 12 - 3);
    level.horizontalBricks(1, 12 - 7, 2);
    level.stairs(6, 2, 4);
    level.verticalBlock(12, 12 - 7, 4);
    level.verticalBlock(13, 12 - 8, 3);
    level.verticalBlock(14, 12 - 9, 2);
    level.verticalBlock(15, 12 - 10, 1);
    level.nextPage(); //8
    
    level.stairs(4, 2, 4);
    level.verticalBlock(8, 12 - 7, 4);
    level.hole(9, 2);
    level.verticalBlock(11, 12 - 7, 4);
    level.verticalBlock(12, 12 - 8, 3);
    level.verticalBlock(13, 12 - 9, 2);
    level.verticalBlock(14, 12 - 10, 1);
    level.nextPage(); //9
    
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.horizontalBricks(8, 12 - 7, 2);
    level.questionBlock(10, 12 - 7);
    level.horizontalBricks(11, 12 - 7, 1);
    level.nextPage(); //10
    
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.stairs(5, 2, 8);
    level.verticalBlock(13, 12 - 3, 8);
    level.nextPage(); //11
    
    level.pole(6, 2);
    level.castle(10, 2);
    level.resetPageIndex();
    
    level.nextPage();
    //setRoomChange 0xc2:0
    level.goomba(6, 2);
    level.nextPage();
    level.goomba(8, 2);
    level.nextPage();
    level.goomba2(3, 2);
    level.skipToPage(5);
    level.goomba(0, 10);
    level.goomba(2, 10);
    level.nextPage();
    level.goomba2(1, 2);
    level.koopa(11, 2);
    level.nextPage();
    level.goomba2(2, 2);
    level.goomba2(12, 2);
    level.nextPage();
    level.goomba2(0, 2);
    level.skipToPage(11);
    level.goomba2(-2, 2);
    level.finalize();
}
void createArea1_2(sp::P<sp::Scene> scene)
{
    //complement=0 index=29
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Clouds);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.reverseLPipe(10, 2, 2, 2, SmbLevelBuilder::PipeColor::Green);
    (new PipeEntrance(scene->getRoot(), PipeEntrance::Type::Left, [](){
        createArea1_2a(sp::Scene::get("stage"));
    }))->setPosition(sp::Vector2d(level.getPageIndex() * 16 + 10.5, 3));
    level.nextPage(); //0
    
    level.setScrollStop(-3);
    level.resetPageIndex();
    
    level.finalize();
}
void createArea1_2a(sp::P<sp::Scene> scene)
{
    //complement=0 index=c0
    global_area_data.start_position = sp::Vector2d(2, 13);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Underground, SmbLevelBuilder::Scenery::None);
    sp::Window::getInstance()->setClearColor(sp::Color(0, 0, 0));
    level.setBasic(-1, SmbLevelBuilder::AllBricks);
    level.setBasic(0, 1);
    level.setBasic(5, 1, 1);
    level.questionBlock(10, 12 - 7, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.questionBlockLine(11, 12 - 7, 4);
    level.nextPage(); //0
    
    level.verticalBlock(1, 12 - 10, 1);
    level.verticalBlock(3, 12 - 9, 2);
    level.verticalBlock(5, 12 - 8, 3);
    level.verticalBlock(7, 12 - 7, 4);
    level.verticalBlock(9, 12 - 7, 4);
    level.verticalBlock(11, 12 - 8, 3);
    level.questionBlock(13, 12 - 6, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::MultiCoin);
    level.verticalBlock(15, 12 - 8, 3);
    level.nextPage(); //1
    
    level.verticalBlock(1, 12 - 9, 2);
    level.verticalBricks(7, 12 - 5, 3);
    level.coins(8, 12 - 6, 1);
    level.verticalBricks(8, 12 - 7, 1);
    level.verticalBricks(9, 12 - 5, 3);
    level.coins(9, 12 - 3, 4);
    level.horizontalBricks(10, 12 - 5, 2);
    level.verticalBricks(12, 12 - 5, 3);
    level.coins(13, 12 - 6, 1);
    level.horizontalBricks(13, 12 - 7, 1);
    level.questionBlock(14, 12 - 5, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::Star);
    level.verticalBricks(14, 12 - 6, 2);
    level.nextPage(); //2
    
    level.setBasic(3, 1, 1, 5);
    level.setBasic(5, 1, 3);
    level.verticalBricks(6, 12 - 7, 3);
    level.verticalBricks(7, 12 - 7, 3);
    level.setBasic(7, 1, 1);
    level.setBasic(9, 1, 3);
    level.coins(10, 12 - 6, 4);
    level.horizontalBricks(10, 12 - 7, 4);
    level.setBasic(13, 1, 8);
    level.setBasic(15, 1, 1);
    level.nextPage(); //3
    
    level.setBasic(1, 1, 3);
    level.verticalBricks(3, 12 - 3, 5);
    level.coins(4, 12 - 6, 1);
    level.horizontalBricks(4, 12 - 7, 2);
    level.questionBlock(5, 12 - 6, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::Upgrade);
    level.setBasic(5, 1, 1);
    level.verticalBricks(8, 12 - 3, 5);
    level.verticalBricks(9, 12 - 3, 3);
    level.questionBlock(9, 12 - 6, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::MultiCoin);
    level.verticalBricks(9, 12 - 7, 1);
    level.setBasic(11, 1, 3);
    level.horizontalBricks(12, 12 - 7, 4);
    level.setBasic(15, 1, 1);
    level.nextPage(); //4
    
    level.hole(0, 3);
    level.coins(4, 12 - 3, 6);
    level.horizontalBricks(4, 12 - 5, 5);
    level.horizontalBricks(4, 12 - 6, 5);
    level.questionBlock(9, 12 - 0, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::Life);
    level.verticalBricks(9, 12 - 5, 2);
    level.nextPage(); //5
    
    level.pipe(7, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(7, 12 - 8);
    //enter pipe(7, 12 - 8);
    level.pipe(13, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(13, 12 - 7);
    level.nextPage(); //6
    
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.hole(8, 2);
    level.verticalBricks(10, 12 - 8, 3);
    level.verticalBricks(11, 12 - 8, 3);
    level.hole(12, 2);
    level.nextPage(); //7
    
    level.stairs(5, 2, 4);
    level.verticalBlock(9, 12 - 7, 4);
    level.setBasic(9, 0);
    level.nextPage(); //8
    
    level.setBasic(0, 1);
    level.horizontalBricks(1, 12 - 6, 5);
    level.questionBlock(6, 12 - 6, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::Upgrade);
    level.setBasic(8, 0);
    level.setBasic(15, 1);
    level.nextPage(); //9
    
    level.verticalBricks(0, 12 - 8, 3);
    level.setBasic(0, 4, 1);
    level.reverseLPipe(6, 12 - 7, 2, 7, SmbLevelBuilder::PipeColor::Green);
    (new PipeEntrance(scene->getRoot(), PipeEntrance::Type::Left, [](){
        createFinish(sp::Scene::get("stage"));
    }))->setPosition(sp::Vector2d(level.getPageIndex() * 16 + 6.5, 6));
    level.setBasic(9, SmbLevelBuilder::AllBricks);
    level.nextPage(); //10
    
    level.setBasic(0, 1, 1);
    level.setScrollStop(-4);
    level.pipe(2, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(2, 12 - 8);
    //enter pipe(2, 12 - 8);
    level.pipe(6, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(6, 12 - 8);
    //enter pipe(6, 12 - 8);
    level.pipe(10, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(10, 12 - 8);
    //enter pipe(10, 12 - 8);
    level.setBasic(10, 1);
    level.setBasic(13, SmbLevelBuilder::AllBricks);
    level.nextPage(); //11
    
    level.setScrollStop(0); //warpzone
    level.resetPageIndex();
    
    level.nextPage();
    level.goomba(0, 2);
    level.goomba(1, 3);
    level.goomba(13, 2);
    level.nextPage();
    //setRoomChange 0xc2:2
    level.koopa2(12, 2);
    level.nextPage();
    level.koopa(11, 2);
    level.goomba(14, 2);
    level.nextPage();
    level.goomba(0, 2);
    level.goomba(9, 10);
    level.goomba2(12, 6);
    level.skipToPage(6);
    level.goomba3(3, 2);
    level.nextPage();
    level.goomba(1, 2);
    level.nextPage();
    level.goomba2(7, 6);
    level.lift(11, 7, Lift::Type::Down, Lift::Size::Default);
    level.lift(11, 1, Lift::Type::Down, Lift::Size::Default);
    level.nextPage();
    level.koopa(2, 2, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.lift(10, 13, Lift::Type::Up, Lift::Size::Default);
    level.lift(10, 5, Lift::Type::Up, Lift::Size::Default);
    //setRoomChange 0x25:11
    level.nextPage();
    //level.warpzone... 2
    level.finalize();
}
void createArea1_3(sp::P<sp::Scene> scene)
{
    //complement=0 index=26
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Clouds);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.setBasic(15, 0);
    level.nextPage(); //0
    
    level.island(2, 12 - 10, 4);
    level.island(8, 12 - 7, 8);
    level.island(10, 12 - 3, 5);
    level.coins(11, 12 - 2, 3);
    level.nextPage(); //1
    
    level.island(0, 12 - 10, 3);
    level.coins(1, 12 - 9, 1);
    level.island(3, 12 - 6, 5);
    level.coins(5, 12 - 0, 2);
    level.island(8, 12 - 2, 7);
    level.nextPage(); //2
    
    level.island(2, 12 - 11, 4);
    level.coins(2, 12 - 4, 2);
    level.island(11, 12 - 11, 5);
    level.questionBlock(11, 12 - 8, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.coins(12, 12 - 2, 4);
    level.island(12, 12 - 3, 4);
    level.nextPage(); //3
    
    level.island(1, 12 - 11, 5);
    level.island(6, 12 - 7, 3);
    level.island(12, 12 - 4, 6);
    level.nextPage(); //4
    
    level.coins(5, 12 - 3, 2);
    level.coins(13, 12 - 2, 2);
    level.nextPage(); //5
    
    level.coins(1, 12 - 2, 2);
    level.island(2, 12 - 9, 4);
    level.island(8, 12 - 5, 8);
    level.nextPage(); //6
    
    level.island(1, 12 - 11, 3);
    level.coins(1, 12 - 10, 3);
    level.island(4, 12 - 7, 4);
    level.coins(8, 12 - 3, 2);
    level.island(10, 12 - 7, 4);
    level.nextPage(); //7
    
    level.setBasic(0, 1);
    level.verticalBlock(10, 12 - 7, 4);
    level.verticalBlock(11, 12 - 7, 4);
    level.verticalBlock(12, 12 - 5, 6);
    level.verticalBlock(13, 12 - 5, 6);
    level.stopContinuousGeneration(7);
    level.verticalBlock(14, 12 - 3, 8);
    level.verticalBlock(15, 12 - 3, 8);
    level.nextPage(); //8
    
    level.pole(8, 2);
    //set background1(10, 2)
    level.largeCastle(11, 2);
    level.resetPageIndex();
    
    level.nextPage();
    level.koopa(14, 10, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.nextPage();
    level.goomba(12, 11);
    level.goomba(14, 11);
    level.nextPage();
    level.lift(7, 8, Lift::Type::UpDown, Lift::Size::Default);
    level.nextPage();
    level.koopa(10, 10, Koopa::Type::ParatroopaRed, Koopa::Behaviour::FlyingUpDown);
    level.nextPage();
    level.goomba(0, 10);
    level.lift(6, 6, Lift::Type::LeftRight, Lift::Size::Default);
    level.lift(14, 5, Lift::Type::LeftRight, Lift::Size::Default);
    level.nextPage();
    level.koopa(14, 8, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.nextPage();
    level.koopa(2, 9, Koopa::Type::ParatroopaRed, Koopa::Behaviour::FlyingUpDown);
    level.nextPage();
    level.lift(3, 8, Lift::Type::LeftRight, Lift::Size::Default);
    level.koopa(5, 2, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.finalize();
}
void createArea1_4(sp::P<sp::Scene> scene)
{
    //complement=0 index=60
    global_area_data.start_position = sp::Vector2d(2, 8);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Castle, SmbLevelBuilder::Scenery::None);
    sp::Window::getInstance()->setClearColor(sp::Color(0, 0, 0));
    level.setBasic(-1, 4, 3);
    level.horizontalBlock(0, 12 - 5, 3);
    level.horizontalBlock(0, 12 - 6, 4);
    level.horizontalBlock(0, 12 - 7, 5);
    level.setBasic(12, 1, 3);
    level.holeWithWater(13, 2);
    level.setBasic(14, 4, 3);
    level.nextPage(); //0
    
    level.verticalBlock(7, 12 - 3, 1);
    level.emptyQuestionBlock(7, 12 - 4);
    level.setBasic(7, 4, 1);
    level.setBasic(9, 0, 1);
    level.setBasic(12, 4, 1);
    level.questionBlock(14, 12 - 4, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.emptyQuestionBlock(14, 12 - 8);
    level.setBasic(15, 0, 1);
    level.nextPage(); //1
    
    level.setBasic(2, 5, 1);
    level.setBasic(4, 5, 4);
    level.emptyQuestionBlock(5, 12 - 4);
    level.nextPage(); //2
    
    level.emptyQuestionBlock(1, 12 - 4);
    level.emptyQuestionBlock(12, 12 - 4);
    level.nextPage(); //3
    
    level.emptyQuestionBlock(3, 12 - 4);
    level.setBasic(7, 4, 1);
    level.emptyQuestionBlock(12, 12 - 7);
    level.nextPage(); //4
    
    level.verticalBlock(0, 12 - 1, 1);
    level.emptyQuestionBlock(0, 12 - 2);
    level.emptyQuestionBlock(4, 12 - 7);
    level.verticalBlock(8, 12 - 1, 1);
    level.emptyQuestionBlock(8, 12 - 2);
    level.emptyQuestionBlock(12, 12 - 7);
    level.nextPage(); //5
    
    level.setBasic(0, 4, 3);
    level.setBasic(7, 1, 1);
    level.questionBlock(10, 12 - 7, QuestionBlock::Type::Hidden);
    level.questionBlock(11, 12 - 3, QuestionBlock::Type::Hidden);
    level.questionBlock(13, 12 - 7, QuestionBlock::Type::Hidden);
    level.questionBlock(14, 12 - 3, QuestionBlock::Type::Hidden);
    level.nextPage(); //6
    
    level.questionBlock(0, 12 - 7, QuestionBlock::Type::Hidden);
    level.questionBlock(1, 12 - 3, QuestionBlock::Type::Hidden);
    level.setBasic(3, 4, 1);
    level.setBasic(7, 1, 1);
    level.setBasic(10, 4, 3);
    level.setBasic(15, 0, 1);
    level.nextPage(); //7
    
    level.castleBridge(0, 4, 13);
    level.bridgeRope(12, 5);
    level.setBasic(12, 5, 1);
    level.setBasic(13, 5, 4);
    level.bridgeAxe(13, 6);
    level.setBasic(15, 1, 1);
    level.nextPage(); //8
    
    level.setScrollStop(-1);
    level.resetPageIndex();
    
    level.nextPage();
    level.fireBar(14, 4, FireBar::Type::Left);
    level.nextPage();
    level.nextPage();
    level.fireBar(1, 8, FireBar::Type::Left);
    level.fireBar(12, 8, FireBar::Type::Left);
    level.nextPage();
    level.fireBar(3, 8, FireBar::Type::Left);
    level.fireBar(12, 5, FireBar::Type::Left);
    level.nextPage();
    level.fireBar(4, 5, FireBar::Type::Left);
    level.fireBar(8, 10, FireBar::Type::Right);
    level.nextPage();
    level.startBowserFire(8);
    level.skipToPage(8);
    level.bowser(7, 5);
    level.lift(10, 8, Lift::Type::LeftRight, Lift::Size::Small);
    level.nextPage();
    level.toad(9, 2);
    level.finalize();
}
void createArea2_1(sp::P<sp::Scene> scene)
{
    //complement=0 index=28
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Fence);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.largeCastle(-2, 2);
    //set background1(6, 0)
    level.horizontalBricks(15, 12 - 7, 1);
    level.nextPage(); //0
    
    level.questionBlock(0, 12 - 7, QuestionBlock::Type::Brick, QuestionBlock::Contents::Upgrade);
    level.horizontalBricks(1, 12 - 7, 1);
    level.stairs(4, 2, 5);
    level.questionBlock(12, 12 - 3, QuestionBlock::Type::Hidden, QuestionBlock::Contents::Life);
    level.questionBlock(12, 12 - 7, QuestionBlock::Type::Hidden);
    level.horizontalBricks(13, 12 - 3, 3);
    level.nextPage(); //1
    
    level.verticalBlock(2, 12 - 7, 4);
    level.verticalBlock(3, 12 - 9, 2);
    level.pipe(14, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(14, 12 - 7);
    level.nextPage(); //2
    
    level.questionBlock(5, 12 - 3);
    level.questionBlock(6, 12 - 3);
    level.questionBlock(7, 12 - 3);
    level.questionBlock(8, 12 - 3);
    level.questionBlock(9, 12 - 3);
    level.questionBlock(5, 12 - 7, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.questionBlockLine(6, 12 - 7, 4);
    level.nextPage(); //3
    
    level.horizontalBricks(4, 12 - 7, 1);
    level.questionBlock(5, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Star);
    level.horizontalBricks(6, 12 - 3, 3);
    level.pipe(10, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(10, 12 - 7);
    level.questionBlockLine(15, 12 - 7, 4);
    level.nextPage(); //4
    
    level.horizontalBricks(1, 12 - 3, 2);
    level.questionBlock(3, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Vine);
    level.horizontalBricks(4, 12 - 3, 2);
    level.questionBlockLine(5, 12 - 7, 3);
    level.horizontalBricks(12, 12 - 3, 4);
    level.hole(12, 4);
    level.nextPage(); //5
    
    level.pipe(7, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(7, 12 - 7);
    //enter pipe(7, 12 - 7);
    level.hole(10, 3);
    level.nextPage(); //6
    
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.pipe(10, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(10, 12 - 7);
    level.questionBlock(13, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Upgrade);
    level.pipe(14, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(14, 12 - 8);
    level.horizontalBricks(14, 12 - 3, 3);
    level.nextPage(); //7
    
    level.pipe(2, 12 - 6, 5, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(2, 12 - 6);
    level.hole(11, 3);
    level.nextPage(); //8
    
    level.hole(8, 2);
    level.verticalBlock(10, 12 - 8, 3);
    level.nextPage(); //9
    
    level.questionBlock(1, 12 - 7, QuestionBlock::Type::Brick, QuestionBlock::Contents::MultiCoin);
    level.horizontalBricks(4, 12 - 3, 5);
    level.questionBlock(10, 12 - 7);
    level.questionBlock(12, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Upgrade);
    level.nextPage(); //10
    
    level.pipe(0, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(0, 12 - 8);
    level.horizontalBricks(9, 12 - 7, 2);
    level.questionBlock(10, 12 - 3, QuestionBlock::Type::Hidden);
    level.trampoline(12, 12 - 9);
    level.verticalBlock(14, 12 - 1, 10);
    level.verticalBlock(15, 12 - 1, 10);
    level.nextPage(); //11
    
    level.pole(8, 2);
    level.castle(12, 2);
    level.resetPageIndex();
    
    level.nextPage();
    level.goomba(8, 8);
    level.nextPage();
    level.koopa(0, 2);
    level.koopa(1, 2);
    level.goomba2(10, 2);
    level.nextPage();
    level.koopa(7, 6);
    level.goomba2(11, 2);
    //setRoomChange 0x2b:0
    level.nextPage();
    level.koopa(2, 2);
    level.goomba3(4, 2);
    level.nextPage();
    level.goomba3(7, 2);
    level.nextPage();
    level.goomba(7, 6);
    //setRoomChange 0x42:0
    level.nextPage();
    level.goomba(4, 4);
    level.goomba(8, 2);
    level.nextPage();
    level.koopa(9, 2);
    level.nextPage();
    level.koopa(7, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.goomba2(2, 2);
    level.koopa(9, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.koopa(11, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.koopa(9, 2);
    level.finalize();
}
void createArea2_2(sp::P<sp::Scene> scene)
{
    //complement=0 index=29
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Clouds);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.reverseLPipe(10, 2, 2, 2, SmbLevelBuilder::PipeColor::Green);
    (new PipeEntrance(scene->getRoot(), PipeEntrance::Type::Left, [](){
        createArea2_2a(sp::Scene::get("stage"));
    }))->setPosition(sp::Vector2d(level.getPageIndex() * 16 + 10.5, 3));
    level.nextPage(); //0
    
    level.setScrollStop(-3);
    level.resetPageIndex();
    
    level.finalize();
}
void createArea2_2a(sp::P<sp::Scene> scene)
{
    //complement=0 index=01
    global_area_data.start_position = sp::Vector2d(2, 13);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Water, SmbLevelBuilder::Scenery::None);
    sp::Window::getInstance()->setClearColor(sp::Color(66/255.0f, 66/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.verticalSeaplant(11, 12 - 8, 3);
    level.coins(14, 12 - 10, 2);
    level.nextPage(); //0
    
    level.horizontalBlock(2, 12 - 7, 3);
    level.coins(11, 12 - 3, 3);
    level.nextPage(); //1
    
    level.verticalSeaplant(1, 12 - 6, 5);
    level.coins(4, 12 - 10, 3);
    level.verticalSeaplant(10, 12 - 5, 2);
    level.horizontalBlock(10, 12 - 7, 2);
    level.nextPage(); //2
    
    level.verticalSeaplant(2, 12 - 7, 4);
    level.nextPage(); //3
    
    level.verticalBlock(0, 12 - 8, 3);
    level.verticalBlock(1, 12 - 6, 5);
    level.hole(2, 5);
    level.coins(3, 12 - 8, 3);
    level.verticalBlock(7, 12 - 6, 5);
    level.verticalBlock(8, 12 - 8, 3);
    level.setBasic(13, 4, 3);
    level.setBasic(15, 1);
    level.nextPage(); //4
    
    level.startUnderwaterCheepCheeps(-6);
    level.horizontalBlock(2, 12 - 3, 3);
    level.verticalSeaplant(3, 12 - 1, 2);
    level.verticalSeaplant(9, 12 - 8, 3);
    level.nextPage(); //5
    
    level.startUnderwaterCheepCheeps(-6);
    level.coins(5, 12 - 9, 3);
    level.verticalSeaplant(6, 12 - 3, 4);
    level.horizontalBlock(6, 12 - 7, 2);
    level.nextPage(); //6
    
    level.coins(1, 12 - 4, 3);
    level.horizontalBlock(3, 12 - 6, 2);
    level.verticalSeaplant(8, 12 - 7, 4);
    level.nextPage(); //7
    
    level.verticalBlock(1, 12 - 7, 4);
    level.verticalBlock(2, 12 - 9, 2);
    level.verticalBlock(3, 12 - 0, 3);
    level.hole(3, 9);
    level.horizontalBlock(4, 12 - 2, 8);
    level.coins(5, 12 - 9, 1);
    level.coins(6, 12 - 10, 3);
    level.coins(9, 12 - 9, 1);
    level.verticalBlock(12, 12 - 9, 2);
    level.verticalBlock(13, 12 - 7, 4);
    level.nextPage(); //8
    
    level.verticalSeaplant(3, 12 - 9, 2);
    level.verticalSeaplant(5, 12 - 8, 3);
    level.verticalBlock(12, 12 - 3, 8);
    level.horizontalBlock(13, 12 - 3, 2);
    level.hole(13, 7);
    level.coins(15, 12 - 7, 3);
    level.coins(15, 12 - 10, 3);
    level.nextPage(); //9
    
    level.horizontalBlock(2, 12 - 3, 2);
    level.verticalBlock(4, 12 - 3, 8);
    level.horizontalBlock(12, 12 - 3, 5);
    level.horizontalBlock(12, 12 - 7, 5);
    level.verticalSeaplant(13, 12 - 1, 2);
    level.nextPage(); //10
    
    level.horizontalBlock(4, 12 - 3, 4);
    level.horizontalBlock(4, 12 - 7, 4);
    level.horizontalBlock(9, 12 - 10, 1);
    level.verticalBlock(10, 12 - 9, 2);
    level.verticalBlock(11, 12 - 8, 3);
    level.setBasic(11, 5, 4);
    level.setBasic(12, SmbLevelBuilder::AllBricks);
    level.sidePipeEntrance(13, 12 - 5, SmbLevelBuilder::PipeColor::Green);
    (new PipeEntrance(scene->getRoot(), PipeEntrance::Type::Left, [](){
        createFinish(sp::Scene::get("stage"));
    }))->setPosition(sp::Vector2d(level.getPageIndex() * 16 + 13.5, 7));
    level.nextPage(); //11
    
    level.stopContinuousGeneration(-6);
    level.setScrollStop(1);
    level.resetPageIndex();
    
    level.skipToPage(1);
    //setRoomChange 0x25:11
    level.blooper(6, 2);
    level.nextPage();
    level.blooper(14, 4);
    level.nextPage();
    level.blooper(7, 3);
    level.nextPage();
    level.blooper(7, 5);
    level.nextPage();
    level.blooper(3, 5);
    level.blooper(14, 10);
    level.nextPage();
    level.blooper(9, 2);
    level.skipToPage(9);
    level.nextPage();
    level.nextPage();
    level.finalize();
}
void createArea2_3(sp::P<sp::Scene> scene)
{
    //complement=0 index=27
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Clouds);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.setBasic(6, 0);
    level.island(8, 12 - 11, 8);
    level.stairs(10, 2, 3);
    level.verticalBlock(13, 12 - 8, 3);
    level.verticalBlock(14, 12 - 8, 3);
    level.bridge(15, 12 - 8, 16);
    level.nextPage(); //0
    
    level.startCheepCheepJumping(4);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //1
    
    level.bridge(0, 12 - 8, 15);
    level.coins(4, 12 - 3, 4);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //2
    
    level.bridge(0, 12 - 8, 16);
    level.coins(7, 12 - 3, 1);
    level.coins(8, 12 - 4, 1);
    level.coins(9, 12 - 3, 1);
    level.coins(10, 12 - 4, 1);
    level.coins(11, 12 - 3, 1);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //3
    
    level.verticalBlock(4, 12 - 8, 5);
    level.bridge(5, 12 - 8, 10);
    level.coins(8, 12 - 3, 1);
    level.coins(9, 12 - 2, 2);
    level.coins(11, 12 - 3, 1);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //4
    
    level.verticalBlock(4, 12 - 8, 5);
    level.bridge(5, 12 - 8, 10);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //5
    
    level.coins(1, 12 - 3, 3);
    level.verticalBlock(3, 12 - 7, 6);
    level.bridge(4, 12 - 7, 5);
    level.questionBlock(6, 12 - 3, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.verticalBlock(9, 12 - 7, 6);
    level.coins(12, 12 - 3, 3);
    level.nextPage(); //6
    
    level.island(0, 12 - 11, 8);
    level.bridge(10, 12 - 8, 3);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //7
    
    level.bridge(0, 12 - 8, 15);
    level.coins(5, 12 - 3, 6);
    level.startCheepCheepJumping(3);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //8
    
    level.verticalBlock(2, 12 - 10, 3);
    level.bridge(3, 12 - 10, 8);
    level.coins(5, 12 - 6, 4);
    level.verticalBlock(11, 12 - 10, 3);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //9
    
    level.bridge(0, 12 - 8, 8);
    level.verticalBlock(8, 12 - 8, 5);
    level.bridge(11, 12 - 8, 2);
    level.coins(13, 12 - 4, 6);
    level.bridge(15, 12 - 8, 2);
    level.nextPage(); //10
    
    level.bridge(3, 12 - 8, 2);
    level.verticalBlock(7, 12 - 8, 5);
    level.bridge(8, 12 - 8, 9);
    level.nextPage(); //11
    
    level.island(0, 12 - 11, 13);
    level.horizontalBlock(1, 12 - 10, 4);
    level.verticalBlock(1, 12 - 8, 2);
    level.verticalBlock(2, 12 - 8, 2);
    level.verticalBlock(3, 12 - 9, 1);
    level.stopContinuousGeneration(-1);
    level.setBasic(14, 1);
    level.nextPage(); //12
    
    level.stairs(0, 2, 8);
    level.verticalBlock(8, 12 - 3, 8);
    level.nextPage(); //13
    
    level.pole(1, 2);
    //set background1(3, 2)
    level.largeCastle(4, 2);
    level.resetPageIndex();
    
    level.skipToPage(2);
    level.nextPage();
    level.nextPage();
    level.nextPage();
    level.skipToPage(7);
    level.nextPage();
    level.skipToPage(138);
    level.finalize();
}
void createArea2_4(sp::P<sp::Scene> scene)
{
    //complement=0 index=62
    global_area_data.start_position = sp::Vector2d(2, 8);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Castle, SmbLevelBuilder::Scenery::None);
    sp::Window::getInstance()->setClearColor(sp::Color(0, 0, 0));
    level.setBasic(-1, 4, 3);
    level.horizontalBlock(0, 12 - 5, 3);
    level.horizontalBlock(0, 12 - 6, 4);
    level.horizontalBlock(0, 12 - 7, 5);
    level.setBasic(15, 0);
    level.nextPage(); //0
    
    level.horizontalBlock(2, 12 - 7, 2);
    level.horizontalBlock(6, 12 - 5, 3);
    level.emptyQuestionBlock(7, 12 - 5);
    level.questionBlock(7, 12 - 1, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.horizontalBlock(11, 12 - 7, 2);
    level.nextPage(); //1
    
    level.verticalBlock(0, 12 - 8, 5);
    level.verticalBlock(1, 12 - 8, 5);
    level.setBasic(1, 1, 4);
    level.horizontalBlock(5, 12 - 7, 12);
    level.emptyQuestionBlock(11, 12 - 11);
    level.nextPage(); //2
    
    level.emptyQuestionBlock(1, 12 - 7);
    level.horizontalBlock(2, 12 - 7, 11);
    level.emptyQuestionBlock(7, 12 - 3);
    level.emptyQuestionBlock(7, 12 - 11);
    level.emptyQuestionBlock(13, 12 - 7);
    level.horizontalBlock(14, 12 - 7, 11);
    level.nextPage(); //3
    
    level.emptyQuestionBlock(3, 12 - 11);
    level.emptyQuestionBlock(9, 12 - 7);
    level.setBasic(15, 4, 4);
    level.nextPage(); //4
    
    level.emptyQuestionBlock(2, 12 - 4);
    level.setBasic(2, 0);
    //set background1(3, 0)
    level.verticalBlock(3, 12 - 8, 5);
    level.liftRope(6); // 1
    level.liftRope(9); // 1
    //set background1(11, 3)
    level.emptyQuestionBlock(12, 12 - 8);
    level.verticalBlock(12, 12 - 9, 4);
    level.setBasic(12, 4, 3);
    level.setBasic(15, 4, 3);
    level.nextPage(); //5
    
    level.setBasic(2, 1);
    level.coins(6, 12 - 6, 3);
    level.coins(6, 12 - 10, 3);
    level.emptyQuestionBlock(7, 12 - 9);
    level.setBasic(11, 0);
    level.verticalBlock(12, 12 - 8, 5);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //6
    
    level.verticalBlock(0, 12 - 8, 5);
    level.setBasic(2, 4, 3);
    level.setBasic(7, 1, 3);
    level.setBasic(9, 4, 3);
    level.setBasic(11, 1, 3);
    level.setBasic(13, 4, 3);
    level.setBasic(15, 0, 1);
    level.nextPage(); //7
    
    level.horizontalBricks(0, 12 - 3, 6);
    level.castleBridge(0, 4, 13);
    level.bridgeRope(12, 5);
    level.setBasic(12, 5, 1);
    level.bridgeAxe(13, 6);
    level.setBasic(13, 5, 4);
    level.setBasic(15, 1, 1);
    level.nextPage(); //8
    
    level.setScrollStop(-1);
    level.resetPageIndex();
    
    level.nextPage();
    level.podoboo(0, 2);
    level.podoboo(14, 2);
    level.nextPage();
    level.nextPage();
    level.fireBar(1, 5, FireBar::Type::Left);
    level.fireBar(7, 9, FireBar::Type::Left);
    level.fireBar(13, 5, FireBar::Type::Left);
    level.nextPage();
    level.fireBar(9, 5, FireBar::Type::Left);
    level.nextPage();
    level.fireBar(2, 8, FireBar::Type::Left);
    level.lift(6, 4, Lift::Type::Up, Lift::Size::Tiny);
    level.lift(9, 4, Lift::Type::Down, Lift::Size::Tiny);
    level.fireBar(12, 4, FireBar::Type::Right);
    level.nextPage();
    level.startBowserFire(2);
    level.nextPage();
    level.nextPage();
    level.bowser(7, 5);
    level.lift(10, 8, Lift::Type::LeftRight, Lift::Size::Small);
    level.nextPage();
    level.toad(9, 2);
    level.finalize();
}
void createArea3_1(sp::P<sp::Scene> scene)
{
    //complement=0 index=24
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Fence);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.largeCastle(-2, 2);
    //night & snow (TODO: Snow)
    sp::Window::getInstance()->setClearColor(sp::Color(0.1, 0.1, 0.1));
    level.nextPage(); //0
    
    level.questionBlock(0, 12 - 7);
    level.questionBlock(3, 12 - 6);
    level.questionBlock(6, 12 - 6, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.horizontalBricks(10, 12 - 7, 3);
    level.nextPage(); //1
    
    level.pipe(0, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(0, 12 - 8);
    level.pipe(6, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(6, 12 - 7);
    //enter pipe(6, 12 - 7);
    level.hole(13, 3);
    level.nextPage(); //2
    
    level.pipe(9, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(9, 12 - 8);
    level.horizontalBricks(13, 12 - 7, 1);
    level.nextPage(); //3
    
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.stairs(9, 2, 4);
    level.bridge(13, 12 - 7, 8);
    level.holeWithWater(13, 8);
    level.nextPage(); //4
    
    level.questionBlock(2, 12 - 3, QuestionBlock::Type::Hidden, QuestionBlock::Contents::Life);
    level.verticalBlock(5, 12 - 7, 4);
    level.holeWithWater(6, 2);
    level.verticalBlock(8, 12 - 7, 4);
    level.verticalBlock(9, 12 - 9, 2);
    level.questionBlock(10, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Star);
    level.horizontalBricks(11, 12 - 3, 2);
    level.nextPage(); //5
    
    level.pipe(7, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(7, 12 - 7);
    level.horizontalBricks(15, 12 - 3, 2);
    level.horizontalBricks(15, 12 - 7, 11);
    level.nextPage(); //6
    
    level.questionBlock(1, 12 - 3);
    level.horizontalBricks(2, 12 - 3, 3);
    level.questionBlock(5, 12 - 3, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.horizontalBricks(6, 12 - 3, 3);
    level.trampoline(14, 12 - 9);
    level.nextPage(); //7
    
    level.hole(0, 4);
    level.horizontalBricks(1, 12 - 3, 2);
    level.horizontalBricks(1, 12 - 6, 3);
    level.questionBlock(3, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Vine);
    level.stairs(8, 2, 6);
    level.hole(14, 2);
    level.nextPage(); //8
    
    level.horizontalBricks(6, 12 - 3, 1);
    level.horizontalBricks(6, 12 - 7, 1);
    level.questionBlock(7, 12 - 3);
    level.questionBlock(7, 12 - 7);
    level.horizontalBricks(8, 12 - 3, 1);
    level.horizontalBricks(8, 12 - 7, 1);
    level.horizontalBricks(11, 12 - 3, 1);
    level.horizontalBricks(11, 12 - 7, 1);
    level.questionBlock(12, 12 - 3);
    level.questionBlock(12, 12 - 7, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.horizontalBricks(13, 12 - 3, 1);
    level.horizontalBricks(13, 12 - 7, 1);
    level.nextPage(); //9
    
    level.horizontalBricks(6, 12 - 7, 1);
    level.questionBlock(7, 12 - 7, QuestionBlock::Type::Brick, QuestionBlock::Contents::MultiCoin);
    level.horizontalBricks(8, 12 - 7, 3);
    level.verticalBlock(14, 12 - 8, 3);
    level.verticalBlock(15, 12 - 5, 6);
    level.nextPage(); //10
    
    level.hole(1, 3);
    level.stairs(7, 2, 8);
    level.verticalBlock(15, 12 - 3, 8);
    level.nextPage(); //11
    
    level.pole(8, 2);
    level.castle(12, 2);
    level.resetPageIndex();
    
    level.nextPage();
    level.koopa(9, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.koopa(12, 3, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    //setRoomChange 0x42:4
    level.nextPage();
    level.goomba(5, 2);
    level.nextPage();
    level.goomba3(5, 2);
    level.nextPage();
    level.koopa(1, 2);
    level.nextPage();
    level.goomba3(2, 6);
    level.nextPage();
    level.goomba2(-2, 2);
    level.koopa(5, 2);
    level.nextPage();
    level.hammerBrother(1, 6);
    level.hammerBrother(4, 2);
    //setRoomChange 0x34:0
    level.nextPage();
    level.goomba(11, 6);
    level.goomba(12, 7);
    level.nextPage();
    level.koopa(5, 2);
    level.koopa(8, 10);
    level.goomba3(10, 2);
    level.nextPage();
    level.koopa(5, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.koopa(8, 3, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.koopa(10, 7);
    level.koopa(11, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.koopa(12, 8);
    level.koopa(15, 10);
    level.finalize();
}
void createArea3_2(sp::P<sp::Scene> scene)
{
    //complement=0 index=35
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Fence);
    //night & snow (TODO: Snow)
    sp::Window::getInstance()->setClearColor(sp::Color(0.1, 0.1, 0.1));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.skipToPage(3);
    
    level.verticalBlock(1, 12 - 10, 1);
    level.coins(7, 12 - 7, 3);
    level.questionBlock(12, 12 - 4, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.verticalBlock(12, 12 - 8, 3);
    level.nextPage(); //3
    
    level.verticalBlock(11, 12 - 9, 2);
    level.questionBlock(13, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Star);
    level.questionBlock(13, 12 - 7, QuestionBlock::Type::Brick, QuestionBlock::Contents::MultiCoin);
    level.verticalBlock(15, 12 - 9, 2);
    level.nextPage(); //4
    
    level.hole(0, 2);
    level.nextPage(); //5
    
    level.setBasic(4, 1);
    level.nextPage(); //6
    
    level.setBasic(8, 1);
    level.hole(11, 2);
    level.verticalBricks(14, 12 - 4, 1);
    level.verticalBlock(14, 12 - 9, 2);
    level.nextPage(); //7
    
    level.hole(0, 2);
    level.skipToPage(10);
    
    level.coins(8, 12 - 4, 4);
    level.pipe(9, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(9, 12 - 8);
    level.skipToPage(12);
    
    level.stairs(0, 2, 8);
    level.verticalBlock(8, 12 - 3, 8);
    level.nextPage(); //12
    
    level.pole(1, 2);
    level.castle(5, 2);
    level.resetPageIndex();
    
    level.nextPage();
    level.koopa(1, 2);
    level.goomba3(8, 2);
    level.nextPage();
    level.koopa3(1, 2);
    level.koopa2(11, 2);
    level.skipToPage(4);
    level.koopa(2, 2);
    level.goomba3(7, 2);
    level.koopa(14, 2);
    level.nextPage();
    level.koopa(12, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.koopa(15, 2);
    level.nextPage();
    level.goomba3(7, 2);
    level.nextPage();
    level.koopa(6, 2);
    level.koopa3(12, 2);
    level.nextPage();
    level.koopa2(6, 2);
    level.nextPage();
    level.koopa3(2, 2);
    level.koopa(15, 2);
    level.nextPage();
    level.goomba3(3, 2);
    level.goomba3(12, 2);
    level.finalize();
}
void createArea3_3(sp::P<sp::Scene> scene)
{
    //complement=0 index=20
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Clouds);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.setBasic(15, 0);
    level.nextPage(); //0
    
    level.island(2, 12 - 8, 5);
    level.island(6, 12 - 5, 6);
    level.island(14, 12 - 11, 3);
    level.coins(15, 12 - 10, 2);
    level.nextPage(); //1
    
    level.island(4, 12 - 10, 7);
    level.coins(5, 12 - 4, 1);
    level.coins(10, 12 - 4, 3);
    level.island(11, 12 - 7, 4);
    level.island(14, 12 - 9, 10);
    level.island(15, 12 - 5, 6);
    level.nextPage(); //2
    
    level.questionBlock(1, 12 - 1, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.coins(4, 12 - 7, 3);
    level.island(7, 12 - 1, 4);
    level.coins(8, 12 - 0, 2);
    level.nextPage(); //3
    
    level.island(1, 12 - 5, 3);
    level.island(1, 12 - 11, 16);
    level.coins(2, 12 - 4, 1);
    level.island(5, 12 - 5, 3);
    level.coins(6, 12 - 4, 1);
    level.island(9, 12 - 5, 3);
    level.coins(10, 12 - 4, 1);
    level.island(13, 12 - 2, 3);
    level.coins(14, 12 - 1, 1);
    level.nextPage(); //4
    
    level.coins(1, 12 - 3, 1);
    //balance platform horizontal rope: (2, 8);
    //balance platform vertical rope: (2, 3);
    level.island(4, 12 - 9, 4);
    level.coins(8, 12 - 3, 1);
    //balance platform vertical rope: (9, 5);
    level.coins(10, 12 - 3, 1);
    level.nextPage(); //5
    
    level.island(1, 12 - 7, 3);
    level.island(8, 12 - 3, 4);
    level.coins(9, 12 - 2, 2);
    level.island(11, 12 - 9, 5);
    level.island(12, 12 - 5, 3);
    level.coins(12, 12 - 8, 1);
    level.coins(13, 12 - 4, 1);
    level.nextPage(); //6
    
    level.island(4, 12 - 11, 3);
    level.island(7, 12 - 8, 12);
    level.nextPage(); //7
    
    //balance platform horizontal rope: (9, 5);
    //balance platform vertical rope: (9, 2);
    //balance platform vertical rope: (13, 5);
    level.setBasic(15, 1);
    level.nextPage(); //8
    
    level.pole(7, 2);
    //set background1(9, 2)
    level.largeCastle(10, 2);
    level.resetPageIndex();
    
    level.nextPage();
    level.goomba(10, 8);
    level.lift(14, 10, Lift::Type::LeftRight, Lift::Size::Default);
    level.nextPage();
    level.lift(1, 6, Lift::Type::LeftRight, Lift::Size::Default);
    level.nextPage();
    level.koopa(4, 8, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.koopa(6, 4, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.lift(12, 8, Lift::Type::Fall, Lift::Size::Default);
    level.nextPage();
    level.koopa(9, 2, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.nextPage();
    level.liftBalance(1, 8, 8, 6, Lift::Size::Default);
    level.lift(14, 5, Lift::Type::LeftRight, Lift::Size::Default);
    level.nextPage();
    level.lift(0, 9, Lift::Type::LeftRight, Lift::Size::Default);
    level.lift(7, 3, Lift::Type::LeftRight, Lift::Size::Default);
    level.nextPage();
    level.koopa(2, 9, Koopa::Type::ParatroopaRed, Koopa::Behaviour::FlyingUpDown);
    level.koopa(12, 5, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.koopa(14, 5, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.nextPage();
    level.lift(4, 8, Lift::Type::LeftRight, Lift::Size::Default);
    level.liftBalance(8, 9, 12, 6, Lift::Size::Default);
    level.finalize();
}
void createArea3_4(sp::P<sp::Scene> scene)
{
    //complement=0 index=63
    global_area_data.start_position = sp::Vector2d(2, 8);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Castle, SmbLevelBuilder::Scenery::None);
    sp::Window::getInstance()->setClearColor(sp::Color(0, 0, 0));
    level.setBasic(-1, 4, 3);
    level.horizontalBlock(0, 12 - 5, 3);
    level.horizontalBlock(0, 12 - 6, 4);
    level.horizontalBlock(0, 12 - 7, 5);
    level.setBasic(15, 4, 1);
    level.nextPage(); //0
    
    level.hole(0, 2);
    level.emptyQuestionBlock(3, 12 - 9);
    level.hole(5, 2);
    level.emptyQuestionBlock(8, 12 - 9);
    level.hole(10, 2);
    level.emptyQuestionBlock(13, 12 - 9);
    level.hole(15, 2);
    level.nextPage(); //1
    
    level.setBasic(2, 1, 3);
    level.questionBlock(10, 12 - 7);
    level.questionBlock(11, 12 - 7, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.questionBlock(12, 12 - 7);
    level.setBasic(13, 0, 1);
    level.setBasic(15, 1, 1);
    level.nextPage(); //2
    
    level.setBasic(4, 1, 3);
    level.horizontalBlock(5, 12 - 10, 3);
    level.emptyQuestionBlock(6, 12 - 3);
    level.emptyQuestionBlock(6, 12 - 9);
    level.setBasic(7, 1, 1);
    level.setBasic(14, 1, 3);
    level.horizontalBlock(15, 12 - 10, 3);
    level.nextPage(); //3
    
    level.emptyQuestionBlock(0, 12 - 3);
    level.emptyQuestionBlock(0, 12 - 9);
    level.setBasic(1, 1, 1);
    level.setBasic(14, 1, 3);
    level.horizontalBlock(15, 12 - 10, 3);
    level.nextPage(); //4
    
    level.emptyQuestionBlock(0, 12 - 3);
    level.emptyQuestionBlock(0, 12 - 9);
    level.coins(1, 12 - 4, 3);
    level.setBasic(1, 1, 1);
    level.setBasic(7, 0, 1);
    level.setBasic(9, 4, 3);
    level.setBasic(15, 0, 1);
    level.nextPage(); //5
    
    level.setBasic(2, 4, 1);
    level.setBasic(5, 0, 1);
    level.setBasic(8, 4, 1);
    level.setBasic(11, 0, 1);
    level.setBasic(14, 4, 3);
    level.nextPage(); //6
    
    level.setBasic(3, 1, 3);
    level.setBasic(5, 4, 3);
    level.setBasic(15, 0, 1);
    level.nextPage(); //7
    
    level.castleBridge(0, 4, 13);
    level.verticalBricks(4, 12 - 1, 3);
    level.verticalBricks(5, 12 - 1, 3);
    level.bridgeRope(12, 5);
    level.setBasic(12, 5, 1);
    level.setBasic(13, 5, 4);
    level.bridgeAxe(13, 6);
    level.setBasic(15, 1, 1);
    level.nextPage(); //8
    
    level.setScrollStop(-1);
    level.resetPageIndex();
    
    level.nextPage();
    level.podoboo(0, 2);
    level.fireBar(3, 3, FireBar::Type::Left);
    level.fireBar(8, 3, FireBar::Type::Left);
    level.podoboo(10, 2);
    level.fireBar(13, 3, FireBar::Type::Left);
    level.skipToPage(3);
    level.fireBar(6, 9, FireBar::Type::Left);
    level.fireBar(6, 3, FireBar::Type::Right);
    level.nextPage();
    level.fireBar(0, 9, FireBar::Type::Left);
    level.fireBar(0, 3, FireBar::Type::Right);
    level.nextPage();
    level.fireBar(0, 9, FireBar::Type::Right);
    level.fireBar(0, 3, FireBar::Type::Left);
    level.podoboo(8, 2);
    level.nextPage();
    level.podoboo(1, 2);
    level.startBowserFire(7);
    level.podoboo(7, 2);
    level.podoboo(13, 2);
    level.skipToPage(8);
    level.bowser(7, 5);
    level.lift(10, 8, Lift::Type::LeftRight, Lift::Size::Small);
    level.nextPage();
    level.toad(9, 2);
    level.finalize();
}
void createArea4_1(sp::P<sp::Scene> scene)
{
    //complement=0 index=22
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Mountain);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.largeCastle(-2, 2);
    //set background1(6, 0)
    level.nextPage(); //0
    
    level.pipe(5, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(5, 12 - 8);
    level.questionBlock(9, 12 - 3);
    level.questionBlock(9, 12 - 7, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.nextPage(); //1
    
    level.hole(0, 2);
    level.coins(9, 12 - 7, 1);
    level.coins(10, 12 - 6, 2);
    level.coins(12, 12 - 7, 1);
    level.skipToPage(4);
    
    level.questionBlock(0, 12 - 3);
    level.questionBlock(0, 12 - 7);
    level.questionBlock(2, 12 - 3);
    level.questionBlock(2, 12 - 7);
    level.hole(14, 4);
    level.nextPage(); //4
    
    level.questionBlockLine(10, 12 - 7, 4);
    level.questionBlock(12, 12 - 3, QuestionBlock::Type::Hidden, QuestionBlock::Contents::Life);
    level.nextPage(); //5
    
    level.verticalBlock(7, 12 - 8, 3);
    level.coins(9, 12 - 4, 4);
    level.nextPage(); //6
    
    level.pipe(4, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(4, 12 - 7);
    level.coins(7, 12 - 4, 4);
    level.nextPage(); //7
    
    level.pipe(4, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(4, 12 - 7);
    //enter pipe(4, 12 - 7);
    level.coins(7, 12 - 4, 4);
    level.nextPage(); //8
    
    level.questionBlockLine(2, 12 - 7, 2);
    level.questionBlock(4, 12 - 3);
    level.questionBlock(5, 12 - 3);
    level.questionBlock(6, 12 - 3);
    level.questionBlock(7, 12 - 3);
    level.questionBlock(4, 12 - 7, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.horizontalBricks(5, 12 - 7, 2);
    level.hole(5, 2);
    level.questionBlockLine(7, 12 - 7, 3);
    level.nextPage(); //9
    
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.hole(14, 3);
    level.nextPage(); //10
    
    level.hole(4, 2);
    level.verticalBlock(13, 12 - 8, 3);
    level.hole(14, 2);
    level.skipToPage(13);
    
    level.stairs(0, 2, 8);
    level.verticalBlock(8, 12 - 3, 8);
    level.questionBlock(12, 12 - 7, QuestionBlock::Type::Brick, QuestionBlock::Contents::MultiCoin);
    level.stopContinuousGeneration(8);
    level.nextPage(); //13
    
    level.pole(1, 2);
    level.castle(5, 2);
    level.resetPageIndex();
    
    level.nextPage();
    //setRoomChange 0xc2:6
    level.lakitu(14, 11);
    level.skipToPage(7);
    level.lakitu(0, 11);
    level.skipToPage(12);
    level.lakitu(1, 11);
    level.finalize();
}
void createArea4_2(sp::P<sp::Scene> scene)
{
    //complement=0 index=29
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Clouds);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.reverseLPipe(10, 2, 2, 2, SmbLevelBuilder::PipeColor::Green);
    (new PipeEntrance(scene->getRoot(), PipeEntrance::Type::Left, [](){
        createArea4_2a(sp::Scene::get("stage"));
    }))->setPosition(sp::Vector2d(level.getPageIndex() * 16 + 10.5, 3));
    level.nextPage(); //0
    
    level.setScrollStop(-3);
    level.resetPageIndex();
    
    level.finalize();
}
void createArea4_2a(sp::P<sp::Scene> scene)
{
    //complement=0 index=41
    global_area_data.start_position = sp::Vector2d(2, 13);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Underground, SmbLevelBuilder::Scenery::None);
    sp::Window::getInstance()->setClearColor(sp::Color(0, 0, 0));
    level.setBasic(-1, SmbLevelBuilder::AllBricks);
    level.setBasic(0, 1);
    level.setBasic(5, 1, 1);
    level.hole(11, 2);
    level.hole(15, 2);
    level.nextPage(); //0
    
    level.hole(2, 3);
    level.verticalBricks(4, 12 - 1, 3);
    level.setBasic(4, 1, 4);
    level.horizontalBricks(6, 12 - 7, 6);
    level.horizontalBricks(6, 12 - 8, 5);
    level.horizontalBricks(6, 12 - 9, 5);
    level.coins(11, 12 - 10, 3);
    level.questionBlock(12, 12 - 7, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::Upgrade);
    level.setBasic(13, 5, 4);
    level.nextPage(); //1
    
    level.questionBlock(11, 12 - 2, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::MultiCoin);
    level.setBasic(15, 1, 1);
    level.nextPage(); //2
    
    level.questionBlock(2, 12 - 3);
    level.questionBlock(3, 12 - 3);
    level.questionBlockLine(2, 12 - 7, 2);
    level.questionBlock(6, 12 - 7);
    level.questionBlock(7, 12 - 7, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.questionBlock(8, 12 - 7);
    level.setBasic(8, 0);
    level.setBasic(14, 1);
    level.questionBlock(15, 12 - 6, QuestionBlock::Type::Hidden);
    level.nextPage(); //3
    
    level.questionBlock(0, 12 - 3, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::Vine);
    level.questionBlock(0, 12 - 5, QuestionBlock::Type::Hidden);
    level.horizontalBricks(1, 12 - 3, 2);
    level.questionBlock(1, 12 - 6, QuestionBlock::Type::Hidden);
    level.questionBlock(2, 12 - 7, QuestionBlock::Type::Hidden);
    level.setBasic(2, 1, 1);
    level.pipe(8, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(8, 12 - 8);
    level.horizontalBricks(12, 12 - 7, 1);
    level.questionBlock(13, 12 - 7, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::MultiCoin);
    level.pipe(14, 12 - 4, 7, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(14, 12 - 4);
    level.nextPage(); //4
    
    level.horizontalBricks(0, 12 - 7, 1);
    level.questionBlock(1, 12 - 7, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::Star);
    level.pipe(4, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(4, 12 - 8);
    //enter pipe(4, 12 - 8);
    level.horizontalBricks(7, 12 - 6, 1);
    level.pipe(9, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(9, 12 - 8);
    level.nextPage(); //5
    
    level.verticalBlock(7, 12 - 9, 2);
    level.verticalBlock(8, 12 - 8, 3);
    level.hole(9, 2);
    level.pipe(11, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(11, 12 - 7);
    level.hole(13, 2);
    level.verticalBlock(15, 12 - 8, 3);
    level.setBasic(15, 1);
    level.nextPage(); //6
    
    level.verticalBlock(0, 12 - 8, 3);
    level.setBasic(0, 0);
    level.setBasic(6, 1, 1);
    level.horizontalBricks(7, 12 - 3, 1);
    level.horizontalBricks(7, 12 - 7, 4);
    level.questionBlock(8, 12 - 3, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::Upgrade);
    level.horizontalBricks(9, 12 - 3, 1);
    level.setBasic(10, 0);
    level.setBasic(15, 0, 1);
    level.nextPage(); //7
    
    level.setBasic(0, 1, 1);
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.pipe(10, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(10, 12 - 8);
    level.pipe(14, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(14, 12 - 7);
    level.nextPage(); //8
    
    level.hole(0, 2);
    level.stairs(8, 2, 3);
    level.setBasic(10, 0);
    level.setBasic(15, 1, 4);
    level.nextPage(); //9
    
    level.verticalBricks(0, 12 - 4, 2);
    level.questionBlock(1, 12 - 7, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::Upgrade);
    level.coins(2, 12 - 6, 10);
    level.horizontalBricks(2, 12 - 7, 10);
    level.stairs(13, 2, 4);
    level.setBasic(15, 1, 1);
    level.nextPage(); //10
    
    level.pipe(4, 12 - 4, 7, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(4, 12 - 4);
    level.hole(7, 2);
    level.setBasic(8, 4, 1);
    level.reverseLPipe(11, 12 - 7, 2, 7, SmbLevelBuilder::PipeColor::Green);
    (new PipeEntrance(scene->getRoot(), PipeEntrance::Type::Left, [](){
        createFinish(sp::Scene::get("stage"));
    }))->setPosition(sp::Vector2d(level.getPageIndex() * 16 + 11.5, 6));
    level.setBasic(14, SmbLevelBuilder::AllBricks);
    level.nextPage(); //11
    
    level.setScrollStop(-2);
    level.nextPage(); //12
    
    level.setBasic(0, 1, 1);
    level.pipe(6, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(6, 12 - 8);
    //enter pipe(6, 12 - 8);
    level.setBasic(10, 1);
    level.setBasic(13, SmbLevelBuilder::AllBricks);
    level.nextPage(); //13
    
    level.setScrollStop(0); //warpzone
    level.resetPageIndex();
    
    level.skipToPage(2);
    //setRoomChange 0x2f:0
    level.goomba3(11, 6);
    level.nextPage();
    level.lift(10, 9, Lift::Type::Down, Lift::Size::Default);
    level.nextPage();
    level.koopa(13, 2);
    level.nextPage();
    level.buzzyBeetle(3, 2);
    level.buzzyBeetle(8, 2);
    //setRoomChange 0x42:8
    level.nextPage();
    level.koopa2(4, 2);
    level.nextPage();
    level.lift(2, 9, Lift::Type::Down, Lift::Size::Default);
    level.lift(2, 2, Lift::Type::Down, Lift::Size::Default);
    level.lift(11, 12, Lift::Type::Up, Lift::Size::Default);
    level.lift(11, 5, Lift::Type::Up, Lift::Size::Default);
    level.nextPage();
    level.koopa(9, 2);
    level.nextPage();
    level.buzzyBeetle(10, 5);
    level.lift(11, 9, Lift::Type::Down, Lift::Size::Default);
    level.lift(11, 2, Lift::Type::Down, Lift::Size::Default);
    level.nextPage();
    level.koopa2(8, 2);
    level.nextPage();
    level.buzzyBeetle(3, 2);
    //level.warpzone... 8
    //setRoomChange 0x25:11
    level.finalize();
}
void createArea4_3(sp::P<sp::Scene> scene)
{
    //complement=1 index=2c
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Clouds);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.setBasic(14, 0);
    level.nextPage(); //0
    
    level.mushroomIsland(0, 12 - 11, 5);
    level.mushroomIsland(3, 12 - 3, 5);
    level.coins(4, 12 - 2, 3);
    level.mushroomIsland(7, 12 - 7, 7);
    level.coins(8, 12 - 6, 5);
    level.nextPage(); //1
    
    level.mushroomIsland(0, 12 - 2, 3);
    level.mushroomIsland(4, 12 - 10, 7);
    level.coins(6, 12 - 9, 3);
    level.mushroomIsland(7, 12 - 3, 5);
    level.questionBlock(11, 12 - 0, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.mushroomIsland(12, 12 - 7, 3);
    level.nextPage(); //2
    
    level.coins(0, 12 - 5, 1);
    //balance platform horizontal rope: (1, 8);
    //balance platform vertical rope: (1, 2);
    level.mushroomIsland(3, 12 - 6, 3);
    //balance platform vertical rope: (8, 5);
    level.coins(9, 12 - 1, 1);
    level.nextPage(); //3
    
    level.mushroomIsland(1, 12 - 11, 5);
    level.mushroomIsland(3, 12 - 5, 3);
    level.coins(3, 12 - 4, 3);
    level.coins(6, 12 - 0, 3);
    level.mushroomIsland(6, 12 - 1, 3);
    level.mushroomIsland(8, 12 - 7, 3);
    level.coins(9, 12 - 6, 1);
    level.mushroomIsland(10, 12 - 3, 5);
    level.nextPage(); //4
    
    //balance platform horizontal rope: (1, 9);
    //balance platform vertical rope: (1, 2);
    level.mushroomIsland(4, 12 - 7, 3);
    //balance platform vertical rope: (9, 6);
    //balance platform horizontal rope: (12, 6);
    //balance platform vertical rope: (12, 2);
    level.nextPage(); //5
    
    level.coins(0, 12 - 5, 1);
    //balance platform vertical rope: (1, 6);
    level.mushroomIsland(3, 12 - 9, 3);
    //balance platform horizontal rope: (7, 7);
    //balance platform vertical rope: (7, 2);
    level.coins(8, 12 - 2, 1);
    level.mushroomIsland(9, 12 - 8, 3);
    //balance platform vertical rope: (13, 6);
    level.nextPage(); //6
    
    level.coins(1, 12 - 6, 5);
    level.mushroomIsland(1, 12 - 7, 5);
    level.mushroomIsland(5, 12 - 4, 3);
    level.mushroomIsland(9, 12 - 11, 7);
    level.nextPage(); //7
    
    level.mushroomIsland(2, 12 - 8, 5);
    level.setBasic(12, 1);
    level.nextPage(); //8
    
    level.pole(3, 2);
    //set background1(5, 2)
    level.largeCastle(6, 2);
    level.resetPageIndex();
    
    level.nextPage();
    level.koopa(12, 6, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.koopa(13, 6, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.nextPage();
    level.koopa(4, 11, Koopa::Type::ParatroopaRed, Koopa::Behaviour::FlyingUpDown);
    level.koopa(7, 3, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.nextPage();
    level.liftBalance(0, 9, 7, 6, Lift::Size::Default);
    level.lift(10, 8, Lift::Type::UpDown, Lift::Size::Default);
    level.lift(14, 10, Lift::Type::UpDown, Lift::Size::Default);
    level.nextPage();
    level.koopa(4, 2, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.koopa(14, 10, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.nextPage();
    level.liftBalance(0, 9, 8, 5, Lift::Size::Default);
    level.nextPage();
    level.liftBalance(-5, 9, 0, 5, Lift::Size::Default);
    level.liftBalance(6, 9, 12, 5, Lift::Size::Default);
    level.skipToPage(8);
    level.lift(8, 9, Lift::Type::UpDown, Lift::Size::Default);
    level.finalize();
}
void createArea4_4(sp::P<sp::Scene> scene)
{
    //complement=0 index=61
    global_area_data.start_position = sp::Vector2d(2, 8);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Castle, SmbLevelBuilder::Scenery::None);
    sp::Window::getInstance()->setClearColor(sp::Color(0, 0, 0));
    level.setBasic(-1, 4, 3);
    level.horizontalBlock(0, 12 - 5, 3);
    level.horizontalBlock(0, 12 - 6, 4);
    level.horizontalBlock(0, 12 - 7, 5);
    level.setBasic(5, 0, 1);
    level.verticalBlock(6, 12 - 8, 5);
    level.verticalBlock(9, 12 - 8, 5);
    level.verticalBlock(10, 12 - 8, 5);
    level.setBasic(12, 4, 1);
    level.setBasic(15, 1, 1);
    level.skipToPage(1);
    
    level.setBasic(1, 1, 1, 4);
    level.setBasic(7, 1, 1);
    level.verticalBlock(9, 12 - 4, 4);
    level.verticalBlock(11, 12 - 4, 4);
    level.verticalBlock(13, 12 - 4, 4);
    level.verticalBlock(15, 12 - 4, 4);
    level.nextPage(); //1
    
    level.verticalBlock(1, 12 - 4, 4);
    level.setBasic(2, 1, 1, 4);
    level.setBasic(5, 1, 1);
    level.horizontalBlock(6, 12 - 4, 6);
    level.pipe(8, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(8, 12 - 8);
    level.setBasic(11, 1, 1, 4);
    level.skipToPage(4);
    
    level.setBasic(10, 1, 1);
    level.setBasic(12, 4, 4);
    //loop-da-loop: 12
    level.setBasic(15, 1, 1);
    level.skipToPage(5);
    
    level.horizontalBlock(6, 12 - 8, 2);
    level.setBasic(7, 0, 1);
    level.horizontalBlock(9, 12 - 6, 2);
    level.verticalBlock(10, 12 - 9, 4);
    level.horizontalBlock(10, 12 - 8, 4);
    level.horizontalBlock(13, 12 - 5, 1);
    level.setBasic(14, 1, 1);
    level.verticalBlock(14, 12 - 6, 3);
    level.verticalBlock(15, 12 - 4, 2);
    level.nextPage(); //5
    
    level.horizontalBlock(0, 12 - 4, 2);
    level.horizontalBlock(0, 12 - 8, 16);
    level.horizontalBlock(4, 12 - 4, 4);
    level.verticalBlock(9, 12 - 4, 4);
    level.horizontalBlock(10, 12 - 4, 2);
    level.horizontalBlock(14, 12 - 4, 2);
    level.nextPage(); //6
    
    level.horizontalBlock(0, 12 - 4, 16);
    level.horizontalBlock(0, 12 - 8, 16);
    level.nextPage(); //7
    
    level.horizontalBlock(0, 12 - 4, 16);
    level.horizontalBlock(0, 12 - 8, 16);
    //loop-da-loop: 12
    level.nextPage(); //8
    
    level.verticalBlock(0, 12 - 3, 5);
    level.setBasic(0, 1, 3);
    level.setBasic(2, 1);
    level.setBasic(7, 4, 1);
    level.setBasic(11, 1, 1);
    level.setBasic(13, 4, 1);
    level.setBasic(15, 0, 1);
    level.nextPage(); //9
    
    level.castleBridge(0, 4, 13);
    level.bridgeRope(12, 5);
    level.setBasic(12, 5, 1);
    level.setBasic(13, 5, 4);
    level.bridgeAxe(13, 6);
    level.setBasic(15, 1, 1);
    level.nextPage(); //10
    
    level.setScrollStop(-1);
    level.resetPageIndex();
    
    level.skipToPage(3);
    level.fireBar(5, 8, FireBar::Type::Right);
    level.fireBar(12, 5, FireBar::Type::Right);
    level.skipToPage(7);
    level.fireBar(3, 8, FireBar::Type::Right);
    level.fireBar(10, 4, FireBar::Type::Right);
    level.nextPage();
    level.startBowserFire(4);
    level.skipToPage(10);
    level.fireBar(2, 4, FireBar::Type::Right);
    level.podoboo(5, 2);
    level.bowser(7, 5);
    level.nextPage();
    level.toad(9, 2);
    level.finalize();
}
void createArea5_1(sp::P<sp::Scene> scene)
{
    //complement=2 index=2a
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Fence);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.skipToPage(2);
    
    level.pipe(12, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(12, 12 - 8);
    level.nextPage(); //2
    
    level.hole(1, 2);
    level.pipe(3, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 8);
    level.skipToPage(5);
    
    level.horizontalBlock(9, 12 - 7, 5);
    level.verticalBlock(9, 12 - 8, 3);
    level.horizontalBricks(10, 12 - 3, 1);
    level.questionBlock(11, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Star);
    level.horizontalBricks(12, 12 - 3, 1);
    level.hole(12, 4);
    level.nextPage(); //5
    
    level.bullitTower(15, 12 - 9, 2);
    level.nextPage(); //6
    
    level.hole(2, 2);
    level.verticalBlock(4, 12 - 8, 3);
    level.skipToPage(9);
    
    level.verticalBlock(3, 12 - 7, 4);
    level.questionBlock(4, 12 - 7, QuestionBlock::Type::Hidden, QuestionBlock::Contents::Life);
    level.horizontalBricks(5, 12 - 7, 2);
    level.hole(8, 3);
    level.pipe(12, 12 - 5, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(12, 12 - 5);
    //enter pipe(12, 12 - 5);
    level.horizontalBlock(12, 12 - 7, 2);
    level.bullitTower(15, 12 - 9, 2);
    level.nextPage(); //9
    
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.bullitTower(10, 12 - 9, 2);
    level.nextPage(); //10
    
    level.stairs(6, 2, 5);
    level.verticalBlock(13, 12 - 3, 6);
    level.verticalBlock(14, 12 - 3, 6);
    level.nextPage(); //11
    
    level.pole(7, 2);
    level.castle(11, 2);
    level.resetPageIndex();
    
    level.nextPage();
    level.koopa(0, 2);
    level.goomba3(3, 2);
    level.nextPage();
    level.goomba3(-2, 2);
    level.koopa2(9, 2);
    level.nextPage();
    level.koopa(13, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.goomba3(1, 2);
    level.goomba3(12, 2);
    level.nextPage();
    level.koopa(7, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.goomba3(7, 2);
    level.nextPage();
    level.goomba3(9, 2);
    level.koopa(15, 2);
    level.nextPage();
    level.goomba3(7, 2);
    level.nextPage();
    level.koopa2(0, 2);
    //setRoomChange 0x42:8
    level.skipToPage(11);
    level.koopa(2, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.koopa(6, 6, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.finalize();
}
void createArea5_2(sp::P<sp::Scene> scene)
{
    //complement=2 index=31
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Fence);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.stairs(12, 2, 4);
    level.nextPage(); //0
    
    level.horizontalBlock(0, 12 - 7, 3);
    level.bullitTower(1, 12 - 5, 2);
    level.coins(5, 12 - 2, 3);
    level.trampoline(9, 12 - 9);
    level.hole(10, 3);
    level.horizontalBricks(13, 12 - 3, 5);
    level.coins(13, 12 - 6, 3);
    level.horizontalBricks(13, 12 - 7, 6);
    level.nextPage(); //1
    
    level.questionBlock(2, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Upgrade);
    level.stairs(12, 2, 4);
    level.nextPage(); //2
    
    level.verticalBlock(0, 12 - 7, 4);
    level.verticalBlock(1, 12 - 9, 2);
    level.pipe(7, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(7, 12 - 8);
    //enter pipe(7, 12 - 8);
    level.stairs(14, 2, 4);
    level.nextPage(); //3
    
    level.hole(2, 2);
    level.verticalBlock(4, 12 - 6, 5);
    level.verticalBlock(5, 12 - 5, 6);
    level.verticalBlock(6, 12 - 5, 6);
    level.questionBlockLine(14, 12 - 7, 5);
    level.nextPage(); //4
    
    level.questionBlock(4, 12 - 7, QuestionBlock::Type::Hidden);
    level.questionBlock(5, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Vine);
    level.horizontalBricks(6, 12 - 3, 2);
    level.coins(6, 12 - 2, 2);
    level.horizontalBricks(9, 12 - 6, 3);
    level.coins(9, 12 - 10, 2);
    level.hole(12, 4);
    level.nextPage(); //5
    
    level.bullitTower(11, 12 - 9, 2);
    level.nextPage(); //6
    
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.horizontalBricks(6, 12 - 3, 7);
    level.horizontalBricks(6, 12 - 7, 8);
    level.questionBlock(13, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Star);
    level.hole(15, 2);
    level.nextPage(); //7
    
    level.verticalBlock(1, 12 - 8, 3);
    level.questionBlock(13, 12 - 9, QuestionBlock::Type::Brick, QuestionBlock::Contents::MultiCoin);
    level.questionBlock(14, 12 - 9, QuestionBlock::Type::Brick, QuestionBlock::Contents::Upgrade);
    level.nextPage(); //8
    
    level.hole(0, 7);
    level.horizontalBricks(3, 12 - 7, 3);
    level.horizontalBricks(9, 12 - 3, 5);
    level.nextPage(); //9
    
    level.questionBlock(8, 12 - 7, QuestionBlock::Type::Brick, QuestionBlock::Contents::Upgrade);
    level.hole(10, 3);
    level.coins(12, 12 - 2, 2);
    level.horizontalBricks(12, 12 - 3, 4);
    level.pipe(13, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(13, 12 - 9);
    level.hole(15, 2);
    level.nextPage(); //10
    
    level.stairs(7, 2, 2);
    level.hole(9, 1);
    level.verticalBlock(10, 12 - 7, 4);
    level.verticalBlock(11, 12 - 6, 5);
    level.hole(12, 1);
    level.verticalBlock(13, 12 - 4, 7);
    level.verticalBlock(14, 12 - 3, 8);
    level.verticalBlock(15, 12 - 3, 8);
    level.nextPage(); //11
    
    level.pole(8, 2);
    level.castle(12, 2);
    level.resetPageIndex();
    
    level.nextPage();
    level.koopa(7, 2);
    //setRoomChange 0x0:0
    level.nextPage();
    level.koopa(8, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.hammerBrother(14, 5);
    level.nextPage();
    level.goomba(15, 4);
    level.nextPage();
    level.goomba(1, 6);
    level.nextPage();
    level.hammerBrother(1, 7);
    //setRoomChange 0x2b:0
    level.nextPage();
    level.koopa(10, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.hammerBrother(8, 6);
    level.hammerBrother(12, 10);
    level.nextPage();
    level.buzzyBeetle(8, 2);
    level.buzzyBeetle(9, 2);
    level.buzzyBeetle(10, 2);
    level.nextPage();
    level.goomba(11, 2);
    level.goomba(12, 2);
    level.koopa(13, 10, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.nextPage();
    level.koopa(3, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.koopa(6, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.koopa(10, 6, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.finalize();
}
void createArea5_3(sp::P<sp::Scene> scene)
{
    //complement=0 index=26
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Clouds);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.setBasic(15, 0);
    level.nextPage(); //0
    
    level.island(2, 12 - 10, 4);
    level.island(8, 12 - 7, 8);
    level.island(10, 12 - 3, 5);
    level.coins(11, 12 - 2, 3);
    level.nextPage(); //1
    
    level.island(0, 12 - 10, 3);
    level.coins(1, 12 - 9, 1);
    level.island(3, 12 - 6, 5);
    level.coins(5, 12 - 0, 2);
    level.island(8, 12 - 2, 7);
    level.nextPage(); //2
    
    level.island(2, 12 - 11, 4);
    level.coins(2, 12 - 4, 2);
    level.island(11, 12 - 11, 5);
    level.questionBlock(11, 12 - 8, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.coins(12, 12 - 2, 4);
    level.island(12, 12 - 3, 4);
    level.nextPage(); //3
    
    level.island(1, 12 - 11, 5);
    level.island(6, 12 - 7, 3);
    level.island(12, 12 - 4, 6);
    level.nextPage(); //4
    
    level.coins(5, 12 - 3, 2);
    level.coins(13, 12 - 2, 2);
    level.nextPage(); //5
    
    level.coins(1, 12 - 2, 2);
    level.island(2, 12 - 9, 4);
    level.island(8, 12 - 5, 8);
    level.nextPage(); //6
    
    level.island(1, 12 - 11, 3);
    level.coins(1, 12 - 10, 3);
    level.island(4, 12 - 7, 4);
    level.coins(8, 12 - 3, 2);
    level.island(10, 12 - 7, 4);
    level.nextPage(); //7
    
    level.setBasic(0, 1);
    level.verticalBlock(10, 12 - 7, 4);
    level.verticalBlock(11, 12 - 7, 4);
    level.verticalBlock(12, 12 - 5, 6);
    level.verticalBlock(13, 12 - 5, 6);
    level.stopContinuousGeneration(7);
    level.verticalBlock(14, 12 - 3, 8);
    level.verticalBlock(15, 12 - 3, 8);
    level.nextPage(); //8
    
    level.pole(8, 2);
    //set background1(10, 2)
    level.largeCastle(11, 2);
    level.resetPageIndex();
    
    level.nextPage();
    level.startBullits(-4);
    level.koopa(14, 10, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.nextPage();
    level.goomba(12, 11);
    level.goomba(14, 11);
    level.nextPage();
    level.lift(7, 8, Lift::Type::UpDown, Lift::Size::Small);
    level.nextPage();
    level.koopa(10, 10, Koopa::Type::ParatroopaRed, Koopa::Behaviour::FlyingUpDown);
    level.nextPage();
    level.goomba(0, 10);
    level.startBullits(-4);
    level.lift(6, 6, Lift::Type::LeftRight, Lift::Size::Small);
    level.lift(14, 5, Lift::Type::LeftRight, Lift::Size::Small);
    level.nextPage();
    level.koopa(14, 8, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.nextPage();
    level.koopa(2, 9, Koopa::Type::ParatroopaRed, Koopa::Behaviour::FlyingUpDown);
    level.nextPage();
    level.lift(3, 8, Lift::Type::LeftRight, Lift::Size::Small);
    level.koopa(5, 2, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.finalize();
}
void createArea5_4(sp::P<sp::Scene> scene)
{
    //complement=0 index=62
    global_area_data.start_position = sp::Vector2d(2, 8);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Castle, SmbLevelBuilder::Scenery::None);
    sp::Window::getInstance()->setClearColor(sp::Color(0, 0, 0));
    level.setBasic(-1, 4, 3);
    level.horizontalBlock(0, 12 - 5, 3);
    level.horizontalBlock(0, 12 - 6, 4);
    level.horizontalBlock(0, 12 - 7, 5);
    level.setBasic(15, 0);
    level.nextPage(); //0
    
    level.horizontalBlock(2, 12 - 7, 2);
    level.horizontalBlock(6, 12 - 5, 3);
    level.emptyQuestionBlock(7, 12 - 5);
    level.questionBlock(7, 12 - 1, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.horizontalBlock(11, 12 - 7, 2);
    level.nextPage(); //1
    
    level.verticalBlock(0, 12 - 8, 5);
    level.verticalBlock(1, 12 - 8, 5);
    level.setBasic(1, 1, 4);
    level.horizontalBlock(5, 12 - 7, 12);
    level.emptyQuestionBlock(11, 12 - 11);
    level.nextPage(); //2
    
    level.emptyQuestionBlock(1, 12 - 7);
    level.horizontalBlock(2, 12 - 7, 11);
    level.emptyQuestionBlock(7, 12 - 3);
    level.emptyQuestionBlock(7, 12 - 11);
    level.emptyQuestionBlock(13, 12 - 7);
    level.horizontalBlock(14, 12 - 7, 11);
    level.nextPage(); //3
    
    level.emptyQuestionBlock(3, 12 - 11);
    level.emptyQuestionBlock(9, 12 - 7);
    level.setBasic(15, 4, 4);
    level.nextPage(); //4
    
    level.emptyQuestionBlock(2, 12 - 4);
    level.setBasic(2, 0);
    //set background1(3, 0)
    level.verticalBlock(3, 12 - 8, 5);
    level.liftRope(6); // 1
    level.liftRope(9); // 1
    //set background1(11, 3)
    level.emptyQuestionBlock(12, 12 - 8);
    level.verticalBlock(12, 12 - 9, 4);
    level.setBasic(12, 4, 3);
    level.setBasic(15, 4, 3);
    level.nextPage(); //5
    
    level.setBasic(2, 1);
    level.coins(6, 12 - 6, 3);
    level.coins(6, 12 - 10, 3);
    level.emptyQuestionBlock(7, 12 - 9);
    level.setBasic(11, 0);
    level.verticalBlock(12, 12 - 8, 5);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //6
    
    level.verticalBlock(0, 12 - 8, 5);
    level.setBasic(2, 4, 3);
    level.setBasic(7, 1, 3);
    level.setBasic(9, 4, 3);
    level.setBasic(11, 1, 3);
    level.setBasic(13, 4, 3);
    level.setBasic(15, 0, 1);
    level.nextPage(); //7
    
    level.horizontalBricks(0, 12 - 3, 6);
    level.castleBridge(0, 4, 13);
    level.bridgeRope(12, 5);
    level.setBasic(12, 5, 1);
    level.bridgeAxe(13, 6);
    level.setBasic(13, 5, 4);
    level.setBasic(15, 1, 1);
    level.nextPage(); //8
    
    level.setScrollStop(-1);
    level.resetPageIndex();
    
    level.nextPage();
    level.podoboo(0, 2);
    level.podoboo(4, 2);
    level.fireBar(7, 7, FireBar::Type::Right, FireBar::Size::Long);
    level.podoboo(14, 2);
    level.nextPage();
    level.fireBar(11, 1, FireBar::Type::Right);
    level.nextPage();
    level.fireBar(1, 5, FireBar::Type::Left);
    level.fireBar(7, 9, FireBar::Type::Left);
    level.fireBar(7, 1, FireBar::Type::Right);
    level.fireBar(13, 5, FireBar::Type::Left);
    level.nextPage();
    level.fireBar(3, 1, FireBar::Type::Left);
    level.fireBar(9, 5, FireBar::Type::Left);
    level.nextPage();
    level.fireBar(2, 8, FireBar::Type::Left);
    level.lift(6, 4, Lift::Type::Up, Lift::Size::Tiny);
    level.lift(9, 4, Lift::Type::Down, Lift::Size::Tiny);
    level.fireBar(12, 4, FireBar::Type::Right);
    level.nextPage();
    level.startBowserFire(2);
    level.fireBar(7, 3, FireBar::Type::RightFast);
    level.podoboo(13, 2);
    level.nextPage();
    level.podoboo(1, 2);
    level.nextPage();
    level.podoboo(3, 2);
    level.bowser(7, 5);
    level.lift(10, 8, Lift::Type::LeftRight, Lift::Size::Small);
    level.nextPage();
    level.toad(9, 2);
    level.finalize();
}
void createArea6_1(sp::P<sp::Scene> scene)
{
    //complement=0 index=2e
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Mountain);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.largeCastle(-2, 2);
    //set background1(6, 4)
    level.nextPage(); //0
    
    level.questionBlockLine(0, 12 - 7, 2);
    level.hole(4, 2);
    level.horizontalBlock(10, 12 - 10, 6);
    level.horizontalBlock(13, 12 - 9, 5);
    level.setBasic(14, 0);
    level.nextPage(); //1
    
    level.horizontalBlock(0, 12 - 8, 4);
    level.horizontalBlock(3, 12 - 7, 3);
    level.questionBlock(4, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Upgrade);
    level.setBasic(4, 1);
    level.horizontalBricks(5, 12 - 3, 1);
    level.hole(7, 2);
    level.horizontalBricks(9, 12 - 7, 2);
    level.questionBlock(11, 12 - 7, QuestionBlock::Type::Brick, QuestionBlock::Contents::MultiCoin);
    level.nextPage(); //2
    
    level.hole(9, 2);
    level.coins(14, 12 - 7, 3);
    level.nextPage(); //3
    
    level.stairs(5, 2, 4);
    level.verticalBlock(9, 12 - 7, 4);
    level.hole(10, 3);
    level.coins(12, 12 - 5, 2);
    level.nextPage(); //4
    
    level.verticalBlock(4, 12 - 9, 1);
    level.verticalBlock(5, 12 - 8, 2);
    level.verticalBlock(7, 12 - 6, 5);
    level.verticalBlock(8, 12 - 5, 6);
    level.verticalBlock(9, 12 - 4, 7);
    level.horizontalBricks(10, 12 - 4, 3);
    level.questionBlock(10, 12 - 6, QuestionBlock::Type::Hidden, QuestionBlock::Contents::Life);
    level.horizontalBricks(12, 12 - 8, 3);
    level.hole(13, 3);
    level.nextPage(); //5
    
    level.pipe(6, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(6, 12 - 8);
    level.coins(9, 12 - 6, 3);
    level.nextPage(); //6
    
    level.questionBlock(1, 12 - 3, QuestionBlock::Type::Hidden);
    level.questionBlock(1, 12 - 7, QuestionBlock::Type::Hidden);
    level.stairs(10, 2, 5);
    level.horizontalBricks(15, 12 - 6, 2);
    level.hole(15, 7);
    level.nextPage(); //7
    
    level.questionBlock(2, 12 - 6, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.horizontalBricks(2, 12 - 10, 5);
    level.questionBlock(3, 12 - 6);
    level.hole(8, 1);
    level.stairs(15, 2, 6);
    level.nextPage(); //8
    
    level.setBasic(4, 0);
    level.horizontalBricks(5, 12 - 5, 2);
    level.horizontalBricks(7, 12 - 7, 1);
    level.questionBlock(8, 12 - 7, QuestionBlock::Type::Brick, QuestionBlock::Contents::MultiCoin);
    level.horizontalBricks(8, 12 - 9, 3);
    level.setBasic(10, 1);
    level.nextPage(); //9
    
    level.hole(4, 3);
    level.stairs(9, 2, 5);
    level.hole(14, 2);
    level.nextPage(); //10
    
    level.verticalBlock(0, 12 - 3, 8);
    level.verticalBlock(1, 12 - 3, 8);
    level.stopContinuousGeneration(2);
    level.pole(10, 2);
    level.nextPage(); //11
    
    level.castle(0, 2);
    level.resetPageIndex();
    
    level.skipToPage(2);
    level.lakitu(0, 11);
    level.skipToPage(7);
    level.lakitu(0, 11);
    level.finalize();
}
void createArea6_2(sp::P<sp::Scene> scene)
{
    //complement=0 index=23
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Mountain);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.horizontalBricks(10, 12 - 7, 3);
    level.nextPage(); //0
    
    level.pipe(3, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 7);
    //enter pipe(3, 12 - 7);
    level.horizontalBricks(7, 12 - 3, 1);
    level.questionBlock(8, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::MultiCoin);
    level.questionBlock(8, 12 - 7, QuestionBlock::Type::Hidden);
    level.horizontalBricks(9, 12 - 3, 1);
    level.pipe(12, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(12, 12 - 7);
    level.nextPage(); //1
    
    level.pipe(0, 12 - 4, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(0, 12 - 4);
    level.horizontalBlock(0, 12 - 6, 2);
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.pipe(5, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(5, 12 - 9);
    level.pipe(14, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(14, 12 - 7);
    level.nextPage(); //2
    
    level.horizontalBricks(3, 12 - 7, 1);
    level.questionBlock(4, 12 - 7, QuestionBlock::Type::Brick, QuestionBlock::Contents::Upgrade);
    level.pipe(8, 12 - 6, 5, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(8, 12 - 6);
    //enter pipe(8, 12 - 6);
    level.pipe(14, 12 - 5, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(14, 12 - 5);
    level.horizontalBlock(14, 12 - 7, 2);
    level.nextPage(); //3
    
    level.horizontalBricks(3, 12 - 3, 5);
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.pipe(10, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(10, 12 - 9);
    level.horizontalBricks(13, 12 - 3, 4);
    level.nextPage(); //4
    
    level.pipe(0, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(0, 12 - 8);
    level.questionBlock(1, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Vine);
    level.questionBlock(2, 12 - 7, QuestionBlock::Type::Hidden);
    level.pipe(4, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(4, 12 - 9);
    level.pipe(7, 12 - 5, 6, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(7, 12 - 5);
    level.pipe(14, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(14, 12 - 8);
    level.nextPage(); //5
    
    level.pipe(6, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(6, 12 - 7);
    level.pipe(9, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(9, 12 - 9);
    level.horizontalBricks(14, 12 - 7, 1);
    level.pipe(15, 12 - 4, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(15, 12 - 4);
    level.horizontalBlock(15, 12 - 7, 2);
    level.nextPage(); //6
    
    level.horizontalBricks(1, 12 - 7, 1);
    level.horizontalBricks(3, 12 - 3, 1);
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.horizontalBricks(7, 12 - 3, 9);
    level.hole(11, 6);
    level.nextPage(); //7
    
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.pipe(7, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(7, 12 - 9);
    level.horizontalBricks(10, 12 - 6, 2);
    level.questionBlock(12, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Star);
    level.horizontalBricks(13, 12 - 3, 1);
    level.hole(13, 1);
    level.hole(15, 1);
    level.nextPage(); //8
    
    level.horizontalBricks(0, 12 - 7, 3);
    level.horizontalBricks(1, 12 - 3, 2);
    level.stairs(5, 2, 3);
    level.hole(8, 1);
    level.pipe(9, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(9, 12 - 8);
    //enter pipe(9, 12 - 8);
    level.verticalBlock(12, 12 - 7, 4);
    level.verticalBlock(13, 12 - 9, 2);
    level.nextPage(); //9
    
    level.horizontalBricks(0, 12 - 3, 3);
    level.horizontalBricks(0, 12 - 7, 3);
    level.pipe(7, 12 - 4, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(7, 12 - 4);
    level.horizontalBlock(7, 12 - 7, 2);
    level.pipe(14, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(14, 12 - 7);
    level.nextPage(); //10
    
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.pipe(5, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(5, 12 - 8);
    level.pipe(7, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(7, 12 - 7);
    level.pipe(13, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(13, 12 - 8);
    level.nextPage(); //11
    
    level.stairs(7, 2, 2);
    level.pipe(9, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(9, 12 - 7);
    level.verticalBlock(11, 12 - 6, 5);
    level.verticalBlock(12, 12 - 5, 6);
    level.verticalBlock(13, 12 - 4, 7);
    level.verticalBlock(14, 12 - 3, 8);
    level.verticalBlock(15, 12 - 3, 8);
    level.nextPage(); //12
    
    level.pole(8, 2);
    level.castle(12, 2);
    level.resetPageIndex();
    
    level.nextPage();
    //setRoomChange 0xc2:8
    level.koopa(10, 2);
    level.nextPage();
    level.koopa(11, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.buzzyBeetle(6, 2);
    //setRoomChange 0x0:0
    level.nextPage();
    level.goomba(3, 10);
    level.goomba(4, 10);
    level.nextPage();
    //setRoomChange 0xb4:0
    level.buzzyBeetle(12, 2);
    level.skipToPage(7);
    //setRoomChange 0x42:6
    level.buzzyBeetle(8, 10);
    level.skipToPage(10);
    level.buzzyBeetle(3, 2);
    level.goomba2(9, 2);
    level.skipToPage(12);
    level.koopa(14, 10, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.finalize();
}
void createArea6_3(sp::P<sp::Scene> scene)
{
    //complement=0 index=2d
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Clouds);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.setBasic(15, 0);
    level.nextPage(); //0
    
    level.island(2, 12 - 11, 3);
    level.island(5, 12 - 7, 3);
    level.island(8, 12 - 11, 3);
    level.coins(12, 12 - 0, 2);
    level.island(15, 12 - 7, 4);
    level.nextPage(); //1
    
    level.island(5, 12 - 11, 3);
    level.trampoline(6, 12 - 9);
    level.island(11, 12 - 11, 3);
    level.coins(11, 12 - 2, 7);
    level.nextPage(); //2
    
    level.island(1, 12 - 9, 4);
    level.questionBlock(7, 12 - 1, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.nextPage(); //3
    
    level.island(1, 12 - 7, 5);
    //balance platform horizontal rope: (7, 5);
    //balance platform vertical rope: (7, 2);
    level.coins(9, 12 - 3, 2);
    //balance platform vertical rope: (11, 6);
    //balance platform horizontal rope: (15, 4);
    //balance platform vertical rope: (15, 2);
    level.nextPage(); //4
    
    //balance platform vertical rope: (2, 6);
    level.coins(5, 12 - 0, 3);
    level.island(5, 12 - 1, 3);
    level.island(5, 12 - 8, 5);
    level.island(10, 12 - 6, 3);
    level.island(13, 12 - 11, 3);
    level.nextPage(); //5
    
    level.island(1, 12 - 11, 4);
    level.coins(4, 12 - 6, 4);
    level.island(7, 12 - 11, 3);
    level.startBullits(2);
    level.island(11, 12 - 7, 5);
    level.nextPage(); //6
    
    level.island(1, 12 - 11, 5);
    level.trampoline(4, 12 - 9);
    level.island(11, 12 - 11, 3);
    //balance platform horizontal rope: (15, 4);
    //balance platform vertical rope: (15, 3);
    level.nextPage(); //7
    
    level.coins(0, 12 - 3, 2);
    //balance platform vertical rope: (2, 6);
    level.island(4, 12 - 3, 3);
    level.island(4, 12 - 11, 4);
    level.island(7, 12 - 7, 4);
    level.stopContinuousGeneration(3);
    level.nextPage(); //8
    
    level.coins(1, 12 - 5, 2);
    level.coins(10, 12 - 1, 2);
    level.island(12, 12 - 3, 3);
    level.setBasic(15, 1);
    level.nextPage(); //9
    
    level.pole(7, 2);
    //set background1(9, 2)
    level.largeCastle(10, 2);
    level.resetPageIndex();
    
    level.nextPage();
    level.lift(12, 1, Lift::Type::UpDown, Lift::Size::Small);
    level.nextPage();
    level.lift(11, 9, Lift::Type::LeftRight, Lift::Size::Small);
    level.nextPage();
    level.lift(0, 7, Lift::Type::LeftRight, Lift::Size::Small);
    level.lift(7, 8, Lift::Type::LeftRight, Lift::Size::Small);
    level.lift(12, 2, Lift::Type::UpDown, Lift::Size::Small);
    level.nextPage();
    level.liftBalance(6, 9, 10, 5, Lift::Size::Small);
    level.nextPage();
    level.liftBalance(-2, 9, 1, 5, Lift::Size::Small);
    level.skipToPage(7);
    level.lift(9, 9, Lift::Type::LeftRight, Lift::Size::Small);
    level.nextPage();
    level.liftBalance(-2, 8, 1, 5, Lift::Size::Small);
    level.lift(13, 7, Lift::Type::Fall, Lift::Size::Small);
    level.nextPage();
    level.lift(1, 8, Lift::Type::Fall, Lift::Size::Small);
    level.lift(5, 6, Lift::Type::Fall, Lift::Size::Small);
    level.lift(9, 7, Lift::Type::Fall, Lift::Size::Small);
    level.finalize();
}
void createArea6_4(sp::P<sp::Scene> scene)
{
    //complement=0 index=60
    global_area_data.start_position = sp::Vector2d(2, 8);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Castle, SmbLevelBuilder::Scenery::None);
    sp::Window::getInstance()->setClearColor(sp::Color(0, 0, 0));
    level.setBasic(-1, 4, 3);
    level.horizontalBlock(0, 12 - 5, 3);
    level.horizontalBlock(0, 12 - 6, 4);
    level.horizontalBlock(0, 12 - 7, 5);
    level.setBasic(12, 1, 3);
    level.holeWithWater(13, 2);
    level.setBasic(14, 4, 3);
    level.nextPage(); //0
    
    level.verticalBlock(7, 12 - 3, 1);
    level.emptyQuestionBlock(7, 12 - 4);
    level.setBasic(7, 4, 1);
    level.setBasic(9, 0, 1);
    level.setBasic(12, 4, 1);
    level.questionBlock(14, 12 - 4, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.emptyQuestionBlock(14, 12 - 8);
    level.setBasic(15, 0, 1);
    level.nextPage(); //1
    
    level.setBasic(2, 5, 1);
    level.setBasic(4, 5, 4);
    level.emptyQuestionBlock(5, 12 - 4);
    level.nextPage(); //2
    
    level.emptyQuestionBlock(1, 12 - 4);
    level.emptyQuestionBlock(12, 12 - 4);
    level.nextPage(); //3
    
    level.emptyQuestionBlock(3, 12 - 4);
    level.setBasic(7, 4, 1);
    level.emptyQuestionBlock(12, 12 - 7);
    level.nextPage(); //4
    
    level.verticalBlock(0, 12 - 1, 1);
    level.emptyQuestionBlock(0, 12 - 2);
    level.emptyQuestionBlock(4, 12 - 7);
    level.verticalBlock(8, 12 - 1, 1);
    level.emptyQuestionBlock(8, 12 - 2);
    level.emptyQuestionBlock(12, 12 - 7);
    level.nextPage(); //5
    
    level.setBasic(0, 4, 3);
    level.setBasic(7, 1, 1);
    level.questionBlock(10, 12 - 7, QuestionBlock::Type::Hidden);
    level.questionBlock(11, 12 - 3, QuestionBlock::Type::Hidden);
    level.questionBlock(13, 12 - 7, QuestionBlock::Type::Hidden);
    level.questionBlock(14, 12 - 3, QuestionBlock::Type::Hidden);
    level.nextPage(); //6
    
    level.questionBlock(0, 12 - 7, QuestionBlock::Type::Hidden);
    level.questionBlock(1, 12 - 3, QuestionBlock::Type::Hidden);
    level.setBasic(3, 4, 1);
    level.setBasic(7, 1, 1);
    level.setBasic(10, 4, 3);
    level.setBasic(15, 0, 1);
    level.nextPage(); //7
    
    level.castleBridge(0, 4, 13);
    level.bridgeRope(12, 5);
    level.setBasic(12, 5, 1);
    level.setBasic(13, 5, 4);
    level.bridgeAxe(13, 6);
    level.setBasic(15, 1, 1);
    level.nextPage(); //8
    
    level.setScrollStop(-1);
    level.resetPageIndex();
    
    level.nextPage();
    level.fireBar(7, 8, FireBar::Type::Left);
    level.podoboo(11, 2);
    level.fireBar(14, 4, FireBar::Type::Left);
    level.nextPage();
    level.podoboo(1, 2);
    level.fireBar(5, 8, FireBar::Type::Left);
    level.nextPage();
    level.fireBar(1, 8, FireBar::Type::Left);
    level.fireBar(12, 8, FireBar::Type::Left);
    level.nextPage();
    level.fireBar(3, 8, FireBar::Type::Left);
    level.fireBar(12, 5, FireBar::Type::Left);
    level.nextPage();
    level.fireBar(0, 10, FireBar::Type::Right);
    level.fireBar(4, 5, FireBar::Type::Left);
    level.fireBar(8, 10, FireBar::Type::Right);
    level.fireBar(12, 5, FireBar::Type::Left);
    level.nextPage();
    level.startBowserFire(8);
    level.skipToPage(8);
    level.podoboo(3, 13);
    level.bowser(7, 5);
    level.lift(10, 8, Lift::Type::LeftRight, Lift::Size::Small);
    level.nextPage();
    level.toad(9, 2);
    level.finalize();
}
void createArea7_1(sp::P<sp::Scene> scene)
{
    //complement=2 index=33
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Fence);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.largeCastle(-2, 2);
    //set background1(6, 5)
    level.nextPage(); //0
    
    level.bullitTower(3, 12 - 9, 2);
    level.questionBlock(11, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Upgrade);
    level.horizontalBricks(12, 12 - 3, 2);
    level.bullitTower(12, 12 - 8, 2);
    level.bullitTower(12, 12 - 10, 1);
    level.nextPage(); //1
    
    level.bullitTower(4, 12 - 9, 2);
    level.questionBlockLine(7, 12 - 7, 4);
    level.bullitTower(14, 12 - 8, 3);
    level.nextPage(); //2
    
    level.bullitTower(8, 12 - 8, 2);
    level.bullitTower(8, 12 - 10, 1);
    level.horizontalBricks(14, 12 - 7, 2);
    level.nextPage(); //3
    
    level.bullitTower(0, 12 - 5, 2);
    level.horizontalBlock(0, 12 - 7, 1);
    level.questionBlock(1, 12 - 7, QuestionBlock::Type::Brick, QuestionBlock::Contents::MultiCoin);
    level.horizontalBricks(2, 12 - 7, 1);
    level.bullitTower(4, 12 - 9, 2);
    level.hole(9, 2);
    level.pipe(12, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(12, 12 - 8);
    level.nextPage(); //4
    
    level.horizontalBricks(2, 12 - 3, 7);
    level.horizontalBricks(2, 12 - 7, 7);
    level.questionBlock(13, 12 - 3, QuestionBlock::Type::Hidden, QuestionBlock::Contents::Life);
    level.pipe(13, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(13, 12 - 8);
    //enter pipe(13, 12 - 8);
    level.nextPage(); //5
    
    level.bullitTower(8, 12 - 9, 2);
    level.pipe(13, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(13, 12 - 8);
    level.nextPage(); //6
    
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.bullitTower(10, 12 - 9, 2);
    level.nextPage(); //7
    
    level.pipe(0, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(0, 12 - 9);
    level.horizontalBricks(6, 12 - 3, 5);
    level.horizontalBricks(6, 12 - 7, 5);
    level.verticalBlock(13, 12 - 8, 3);
    level.nextPage(); //8
    
    level.bullitTower(2, 12 - 8, 2);
    level.bullitTower(2, 12 - 10, 1);
    level.horizontalBricks(5, 12 - 6, 2);
    level.questionBlock(7, 12 - 0, QuestionBlock::Type::Brick, QuestionBlock::Contents::Upgrade);
    level.trampoline(7, 12 - 9);
    level.hole(8, 1);
    level.horizontalBricks(9, 12 - 4, 2);
    level.stairs(9, 2, 6);
    level.nextPage(); //9
    
    level.stairs(2, 2, 8);
    level.verticalBlock(10, 12 - 3, 8);
    level.nextPage(); //10
    
    level.pole(3, 2);
    level.castle(7, 2);
    level.resetPageIndex();
    
    level.nextPage();
    level.koopa(10, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    //setRoomChange 0x42:0
    level.nextPage();
    level.koopa(12, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.koopa(5, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.koopa(1, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.hammerBrother(4, 2);
    level.hammerBrother(6, 6);
    level.skipToPage(7);
    level.koopa(2, 2);
    level.nextPage();
    level.hammerBrother(7, 2);
    level.hammerBrother(9, 6);
    level.skipToPage(10);
    level.buzzyBeetle(9, 11);
    level.finalize();
}
void createArea7_2(sp::P<sp::Scene> scene)
{
    //complement=0 index=29
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Clouds);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.reverseLPipe(10, 2, 2, 2, SmbLevelBuilder::PipeColor::Green);
    (new PipeEntrance(scene->getRoot(), PipeEntrance::Type::Left, [](){
        createArea7_2a(sp::Scene::get("stage"));
    }))->setPosition(sp::Vector2d(level.getPageIndex() * 16 + 10.5, 3));
    level.nextPage(); //0
    
    level.setScrollStop(-3);
    level.resetPageIndex();
    
    level.finalize();
}
void createArea7_2a(sp::P<sp::Scene> scene)
{
    //complement=0 index=01
    global_area_data.start_position = sp::Vector2d(2, 13);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Water, SmbLevelBuilder::Scenery::None);
    sp::Window::getInstance()->setClearColor(sp::Color(66/255.0f, 66/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.verticalSeaplant(11, 12 - 8, 3);
    level.coins(14, 12 - 10, 2);
    level.nextPage(); //0
    
    level.horizontalBlock(2, 12 - 7, 3);
    level.coins(11, 12 - 3, 3);
    level.nextPage(); //1
    
    level.verticalSeaplant(1, 12 - 6, 5);
    level.coins(4, 12 - 10, 3);
    level.verticalSeaplant(10, 12 - 5, 2);
    level.horizontalBlock(10, 12 - 7, 2);
    level.nextPage(); //2
    
    level.verticalSeaplant(2, 12 - 7, 4);
    level.nextPage(); //3
    
    level.verticalBlock(0, 12 - 8, 3);
    level.verticalBlock(1, 12 - 6, 5);
    level.hole(2, 5);
    level.coins(3, 12 - 8, 3);
    level.verticalBlock(7, 12 - 6, 5);
    level.verticalBlock(8, 12 - 8, 3);
    level.setBasic(13, 4, 3);
    level.setBasic(15, 1);
    level.nextPage(); //4
    
    level.startUnderwaterCheepCheeps(-6);
    level.horizontalBlock(2, 12 - 3, 3);
    level.verticalSeaplant(3, 12 - 1, 2);
    level.verticalSeaplant(9, 12 - 8, 3);
    level.nextPage(); //5
    
    level.startUnderwaterCheepCheeps(-6);
    level.coins(5, 12 - 9, 3);
    level.verticalSeaplant(6, 12 - 3, 4);
    level.horizontalBlock(6, 12 - 7, 2);
    level.nextPage(); //6
    
    level.coins(1, 12 - 4, 3);
    level.horizontalBlock(3, 12 - 6, 2);
    level.verticalSeaplant(8, 12 - 7, 4);
    level.nextPage(); //7
    
    level.verticalBlock(1, 12 - 7, 4);
    level.verticalBlock(2, 12 - 9, 2);
    level.verticalBlock(3, 12 - 0, 3);
    level.hole(3, 9);
    level.horizontalBlock(4, 12 - 2, 8);
    level.coins(5, 12 - 9, 1);
    level.coins(6, 12 - 10, 3);
    level.coins(9, 12 - 9, 1);
    level.verticalBlock(12, 12 - 9, 2);
    level.verticalBlock(13, 12 - 7, 4);
    level.nextPage(); //8
    
    level.verticalSeaplant(3, 12 - 9, 2);
    level.verticalSeaplant(5, 12 - 8, 3);
    level.verticalBlock(12, 12 - 3, 8);
    level.horizontalBlock(13, 12 - 3, 2);
    level.hole(13, 7);
    level.coins(15, 12 - 7, 3);
    level.coins(15, 12 - 10, 3);
    level.nextPage(); //9
    
    level.horizontalBlock(2, 12 - 3, 2);
    level.verticalBlock(4, 12 - 3, 8);
    level.horizontalBlock(12, 12 - 3, 5);
    level.horizontalBlock(12, 12 - 7, 5);
    level.verticalSeaplant(13, 12 - 1, 2);
    level.nextPage(); //10
    
    level.horizontalBlock(4, 12 - 3, 4);
    level.horizontalBlock(4, 12 - 7, 4);
    level.horizontalBlock(9, 12 - 10, 1);
    level.verticalBlock(10, 12 - 9, 2);
    level.verticalBlock(11, 12 - 8, 3);
    level.setBasic(11, 5, 4);
    level.setBasic(12, SmbLevelBuilder::AllBricks);
    level.sidePipeEntrance(13, 12 - 5, SmbLevelBuilder::PipeColor::Green);
    (new PipeEntrance(scene->getRoot(), PipeEntrance::Type::Left, [](){
        createFinish(sp::Scene::get("stage"));
    }))->setPosition(sp::Vector2d(level.getPageIndex() * 16 + 13.5, 7));
    level.nextPage(); //11
    
    level.stopContinuousGeneration(-6);
    level.setScrollStop(1);
    level.resetPageIndex();
    
    level.skipToPage(1);
    //setRoomChange 0x25:11
    level.blooper(6, 2);
    level.blooper(9, 6);
    level.nextPage();
    level.blooper(14, 4);
    level.nextPage();
    level.blooper(4, 6);
    level.blooper(7, 3);
    level.nextPage();
    level.blooper(13, 7);
    level.blooper(7, 5);
    level.nextPage();
    level.blooper(3, 5);
    level.blooper(10, 2);
    level.blooper(14, 10);
    level.nextPage();
    level.blooper(9, 2);
    level.skipToPage(9);
    level.blooper(6, 5);
    level.nextPage();
    level.blooper(13, 2);
    level.nextPage();
    level.blooper(3, 2);
    level.finalize();
}
void createArea7_3(sp::P<sp::Scene> scene)
{
    //complement=0 index=27
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Clouds);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.setBasic(6, 0);
    level.island(8, 12 - 11, 8);
    level.stairs(10, 2, 3);
    level.verticalBlock(13, 12 - 8, 3);
    level.verticalBlock(14, 12 - 8, 3);
    level.bridge(15, 12 - 8, 16);
    level.nextPage(); //0
    
    level.startCheepCheepJumping(4);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //1
    
    level.bridge(0, 12 - 8, 15);
    level.coins(4, 12 - 3, 4);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //2
    
    level.bridge(0, 12 - 8, 16);
    level.coins(7, 12 - 3, 1);
    level.coins(8, 12 - 4, 1);
    level.coins(9, 12 - 3, 1);
    level.coins(10, 12 - 4, 1);
    level.coins(11, 12 - 3, 1);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //3
    
    level.verticalBlock(4, 12 - 8, 5);
    level.bridge(5, 12 - 8, 10);
    level.coins(8, 12 - 3, 1);
    level.coins(9, 12 - 2, 2);
    level.coins(11, 12 - 3, 1);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //4
    
    level.verticalBlock(4, 12 - 8, 5);
    level.bridge(5, 12 - 8, 10);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //5
    
    level.coins(1, 12 - 3, 3);
    level.verticalBlock(3, 12 - 7, 6);
    level.bridge(4, 12 - 7, 5);
    level.questionBlock(6, 12 - 3, QuestionBlock::Type::Normal, QuestionBlock::Contents::Upgrade);
    level.verticalBlock(9, 12 - 7, 6);
    level.coins(12, 12 - 3, 3);
    level.nextPage(); //6
    
    level.island(0, 12 - 11, 8);
    level.bridge(10, 12 - 8, 3);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //7
    
    level.bridge(0, 12 - 8, 15);
    level.coins(5, 12 - 3, 6);
    level.startCheepCheepJumping(3);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //8
    
    level.verticalBlock(2, 12 - 10, 3);
    level.bridge(3, 12 - 10, 8);
    level.coins(5, 12 - 6, 4);
    level.verticalBlock(11, 12 - 10, 3);
    level.verticalBlock(15, 12 - 8, 5);
    level.nextPage(); //9
    
    level.bridge(0, 12 - 8, 8);
    level.verticalBlock(8, 12 - 8, 5);
    level.bridge(11, 12 - 8, 2);
    level.coins(13, 12 - 4, 6);
    level.bridge(15, 12 - 8, 2);
    level.nextPage(); //10
    
    level.bridge(3, 12 - 8, 2);
    level.verticalBlock(7, 12 - 8, 5);
    level.bridge(8, 12 - 8, 9);
    level.nextPage(); //11
    
    level.island(0, 12 - 11, 13);
    level.horizontalBlock(1, 12 - 10, 4);
    level.verticalBlock(1, 12 - 8, 2);
    level.verticalBlock(2, 12 - 8, 2);
    level.verticalBlock(3, 12 - 9, 1);
    level.stopContinuousGeneration(-1);
    level.setBasic(14, 1);
    level.nextPage(); //12
    
    level.stairs(0, 2, 8);
    level.verticalBlock(8, 12 - 3, 8);
    level.nextPage(); //13
    
    level.pole(1, 2);
    //set background1(3, 2)
    level.largeCastle(4, 2);
    level.resetPageIndex();
    
    level.skipToPage(2);
    level.koopa(7, 5);
    level.nextPage();
    level.koopa(4, 5, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.koopa(15, 5, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.nextPage();
    level.koopa(15, 5, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.skipToPage(7);
    level.koopa(7, 2, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge);
    level.nextPage();
    level.koopa(12, 7, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::FlyingLeftRight);
    level.skipToPage(138);
    level.koopa(12, 5, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::FlyingLeftRight);
    level.finalize();
}
void createArea7_4(sp::P<sp::Scene> scene)
{
    //complement=0 index=64
    global_area_data.start_position = sp::Vector2d(2, 8);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Castle, SmbLevelBuilder::Scenery::None);
    sp::Window::getInstance()->setClearColor(sp::Color(0, 0, 0));
    level.setBasic(-1, 4, 3);
    level.horizontalBlock(0, 12 - 5, 3);
    level.horizontalBlock(0, 12 - 6, 4);
    level.horizontalBlock(0, 12 - 7, 5);
    level.setBasic(15, 0, 1);
    level.nextPage(); //0
    
    level.setBasic(10, 4, 1);
    level.setBasic(11, 4, 3);
    level.setBasic(15, 1, 1);
    level.skipToPage(2);
    
    level.horizontalBlock(2, 12 - 7, 3);
    level.verticalBlock(4, 12 - 6, 2);
    level.verticalBlock(5, 12 - 5, 3);
    level.setBasic(5, 1, 1, 4);
    level.nextPage(); //2
    
    level.setBasic(1, 1, 1);
    level.horizontalBlock(6, 12 - 8, 13);
    level.horizontalBlock(7, 12 - 4, 11);
    //loop-da-loop: 7
    level.nextPage(); //3
    
    level.setBasic(5, 1, 1, 4);
    //loop-da-loop: 7
    level.nextPage(); //4
    
    level.setBasic(7, 1, 1);
    level.verticalBlock(8, 12 - 4, 3);
    level.verticalBlock(9, 12 - 4, 2);
    level.horizontalBlock(10, 12 - 4, 2);
    //loop-da-loop: 11
    level.setBasic(12, 4, 1);
    level.setBasic(15, 1, 1);
    level.skipToPage(6);
    
    level.horizontalBlock(3, 12 - 4, 2);
    level.setBasic(3, 0, 1);
    level.horizontalBlock(6, 12 - 4, 3);
    level.emptyQuestionBlock(7, 12 - 5);
    level.verticalBlock(7, 12 - 11, 2);
    level.horizontalBlock(10, 12 - 4, 4);
    level.setBasic(10, 1, 1);
    level.setBasic(13, 1, 1, 4);
    level.nextPage(); //6
    
    level.setBasic(3, 1, 1);
    level.horizontalBlock(6, 12 - 4, 3);
    level.horizontalBlock(7, 12 - 8, 3);
    level.horizontalBlock(11, 12 - 4, 7);
    level.horizontalBlock(12, 12 - 8, 7);
    //loop-da-loop: 13
    level.nextPage(); //7
    
    level.horizontalBlock(4, 12 - 4, 3);
    level.horizontalBlock(5, 12 - 8, 3);
    level.verticalBlock(9, 12 - 4, 4);
    level.horizontalBlock(10, 12 - 4, 15);
    level.horizontalBlock(11, 12 - 10, 1);
    level.verticalBlock(12, 12 - 9, 2);
    level.setBasic(12, 4, 1);
    //loop-da-loop: 13
    level.nextPage(); //8
    
    level.setBasic(12, 4, 1);
    //loop-da-loop: 13
    level.setBasic(15, 1, 1);
    level.nextPage(); //9
    
    level.setBasic(2, 4, 1);
    level.setBasic(5, 1, 1);
    level.setBasic(7, 4, 1);
    level.setBasic(15, 1, 1);
    level.nextPage(); //10
    
    level.setBasic(1, 4, 1);
    level.setBasic(3, 1, 1);
    level.setBasic(5, 4, 1);
    level.setBasic(7, 1, 1);
    level.setBasic(9, 4, 1);
    level.setBasic(15, 0, 1);
    level.nextPage(); //11
    
    level.castleBridge(0, 4, 13);
    level.bridgeRope(12, 5);
    level.setBasic(12, 5, 1);
    level.setBasic(13, 5, 4);
    level.bridgeAxe(13, 6);
    level.setBasic(15, 1, 1);
    level.nextPage(); //12
    
    level.setScrollStop(-1);
    level.resetPageIndex();
    
    level.nextPage();
    level.lift(2, 7, Lift::Type::Fall, Lift::Size::Small);
    level.podoboo(4, 2);
    level.lift(6, 6, Lift::Type::Fall, Lift::Size::Small);
    level.skipToPage(6);
    level.fireBar(7, 7, FireBar::Type::Right);
    level.skipToPage(11);
    level.startBowserFire(6);
    level.nextPage();
    level.podoboo(4, 2);
    level.bowser(7, 5);
    level.nextPage();
    level.toad(9, 2);
    level.finalize();
}
void createArea8_1(sp::P<sp::Scene> scene)
{
    //complement=0 index=30
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Fence);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.largeCastle(-2, 2);
    //set background1(6, 0)
    level.skipToPage(2);
    
    level.pipe(3, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 7);
    level.hole(14, 1);
    level.nextPage(); //2
    
    level.hole(0, 1);
    level.hole(3, 1);
    level.hole(6, 1);
    level.hole(9, 1);
    level.nextPage(); //3
    
    level.coins(0, 12 - 6, 1);
    level.pipe(12, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(12, 12 - 7);
    level.nextPage(); //4
    
    level.questionBlock(0, 12 - 6, QuestionBlock::Type::Hidden, QuestionBlock::Contents::Life);
    level.pipe(2, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(2, 12 - 8);
    level.coins(9, 12 - 6, 1);
    level.pipe(14, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(14, 12 - 7);
    level.nextPage(); //5
    
    level.coins(2, 12 - 6, 1);
    level.pipe(8, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(8, 12 - 7);
    //enter pipe(8, 12 - 7);
    level.coins(13, 12 - 2, 2);
    level.nextPage(); //6
    
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.nextPage(); //7
    
    level.pipe(12, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(12, 12 - 8);
    level.nextPage(); //8
    
    level.verticalBlock(9, 12 - 7, 4);
    level.horizontalBricks(10, 12 - 3, 4);
    level.questionBlock(14, 12 - 7, QuestionBlock::Type::Hidden);
    level.questionBlock(14, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::MultiCoin);
    level.horizontalBricks(15, 12 - 3, 3);
    level.nextPage(); //9
    
    level.verticalBlock(3, 12 - 7, 4);
    level.hole(9, 1);
    level.hole(11, 1);
    level.hole(14, 1);
    level.nextPage(); //10
    
    level.hole(0, 1);
    level.hole(3, 1);
    level.horizontalBricks(8, 12 - 6, 2);
    level.questionBlock(10, 12 - 6, QuestionBlock::Type::Brick, QuestionBlock::Contents::Star);
    level.horizontalBricks(11, 12 - 6, 5);
    level.nextPage(); //11
    
    level.hole(5, 1);
    level.hole(7, 1);
    level.hole(9, 1);
    level.nextPage(); //12
    
    level.verticalBlock(2, 12 - 9, 2);
    level.hole(13, 6);
    level.coins(15, 12 - 6, 2);
    level.nextPage(); //13
    
    level.hole(13, 1);
    level.pipe(14, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(14, 12 - 8);
    level.nextPage(); //14
    
    level.hole(0, 2);
    level.pipe(2, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(2, 12 - 7);
    level.hole(4, 2);
    level.pipe(6, 12 - 6, 5, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(6, 12 - 6);
    level.skipToPage(17);
    
    level.stairs(3, 2, 6);
    level.coins(11, 12 - 6, 2);
    level.nextPage(); //17
    
    level.hole(2, 3);
    level.coins(3, 12 - 6, 1);
    level.hole(7, 3);
    level.coins(8, 12 - 6, 1);
    level.verticalBlock(15, 12 - 9, 2);
    level.nextPage(); //18
    
    level.verticalBlock(3, 12 - 9, 2);
    level.hole(10, 5);
    level.coins(12, 12 - 6, 2);
    level.nextPage(); //19
    
    level.hole(0, 4);
    level.coins(1, 12 - 6, 2);
    level.nextPage(); //20
    
    level.pipe(8, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(8, 12 - 8);
    level.nextPage(); //21
    
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.hole(7, 1);
    level.verticalBlock(8, 12 - 9, 2);
    level.hole(9, 1);
    level.verticalBlock(10, 12 - 7, 4);
    level.hole(11, 1);
    level.verticalBlock(12, 12 - 5, 6);
    level.hole(13, 1);
    level.verticalBlock(14, 12 - 3, 8);
    level.verticalBlock(15, 12 - 3, 8);
    level.nextPage(); //22
    
    level.pole(8, 2);
    level.castle(12, 2);
    level.resetPageIndex();
    
    level.nextPage();
    level.buzzyBeetle(2, 2);
    level.goomba3(7, 2);
    //setRoomChange 0x42:2
    level.nextPage();
    level.goomba3(-2, 2);
    level.koopa2(11, 2);
    level.nextPage();
    level.koopa(13, 2);
    level.nextPage();
    level.goomba3(5, 2);
    level.nextPage();
    level.buzzyBeetle(1, 2);
    level.nextPage();
    level.goomba3(12, 2);
    level.nextPage();
    level.koopa(7, 2);
    level.koopa3(12, 2);
    level.nextPage();
    level.koopa3(2, 2);
    level.nextPage();
    level.goomba3(4, 2);
    level.nextPage();
    level.koopa(1, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.koopa(12, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.koopa(1, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.skipToPage(13);
    level.koopa2(-1, 2);
    level.nextPage();
    level.goomba3(8, 2);
    level.nextPage();
    level.buzzyBeetle(14, 2);
    level.nextPage();
    level.goomba3(1, 2);
    level.goomba3(8, 2);
    level.nextPage();
    level.goomba2(0, 2);
    level.buzzyBeetle(11, 2);
    level.skipToPage(19);
    level.koopa(1, 2);
    level.nextPage();
    level.koopa(12, 2);
    level.nextPage();
    level.koopa3(3, 2);
    level.finalize();
}
void createArea8_2(sp::P<sp::Scene> scene)
{
    //complement=2 index=32
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Fence);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.hole(15, 1);
    level.nextPage(); //0
    
    level.stairs(1, 2, 4);
    level.hole(5, 1);
    level.verticalBlock(6, 12 - 5, 6);
    level.verticalBlock(7, 12 - 4, 7);
    level.verticalBlock(8, 12 - 3, 8);
    level.verticalBlock(9, 12 - 3, 8);
    level.questionBlockLine(13, 12 - 7, 4);
    level.nextPage(); //1
    
    level.hole(4, 1);
    level.horizontalBricks(11, 12 - 3, 1);
    level.trampoline(12, 12 - 9);
    level.questionBlock(12, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Life);
    level.horizontalBricks(13, 12 - 3, 16);
    level.hole(13, 1);
    level.nextPage(); //2
    
    level.hole(2, 1);
    level.hole(4, 1);
    level.hole(8, 1);
    level.horizontalBricks(13, 12 - 3, 15);
    level.stopContinuousGeneration(8);
    level.hole(15, 1);
    level.nextPage(); //3
    
    level.horizontalBricks(13, 12 - 7, 2);
    level.hole(14, 2);
    level.nextPage(); //4
    
    level.hole(4, 1);
    level.bullitTower(5, 12 - 9, 2);
    level.bullitTower(13, 12 - 8, 2);
    level.bullitTower(13, 12 - 10, 1);
    level.nextPage(); //5
    
    level.horizontalBricks(3, 12 - 7, 1);
    level.questionBlock(4, 12 - 7, QuestionBlock::Type::Brick, QuestionBlock::Contents::Upgrade);
    level.bullitTower(9, 12 - 9, 2);
    level.horizontalBricks(14, 12 - 7, 2);
    level.nextPage(); //6
    
    level.bullitTower(3, 12 - 10, 1);
    level.horizontalBricks(6, 12 - 7, 1);
    level.bullitTower(7, 12 - 6, 1);
    level.verticalBlock(7, 12 - 7, 1);
    level.questionBlock(8, 12 - 7, QuestionBlock::Type::Brick, QuestionBlock::Contents::MultiCoin);
    level.bullitTower(13, 12 - 8, 3);
    level.nextPage(); //7
    
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.hole(10, 1);
    level.pipe(14, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(14, 12 - 9);
    level.nextPage(); //8
    
    level.hole(0, 1);
    level.hole(2, 1);
    level.hole(4, 6);
    level.pipe(12, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(12, 12 - 7);
    //enter pipe(12, 12 - 7);
    level.nextPage(); //9
    
    level.pipe(3, 12 - 9, 2, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.hole(14, 1);
    level.bullitTower(15, 12 - 9, 2);
    level.nextPage(); //10
    
    level.hole(0, 3);
    level.stairs(6, 2, 5);
    level.bullitTower(15, 12 - 8, 2);
    level.bullitTower(15, 12 - 10, 1);
    level.nextPage(); //11
    
    level.stairs(7, 2, 3);
    level.hole(10, 1);
    level.verticalBlock(11, 12 - 6, 5);
    level.hole(12, 2);
    level.verticalBlock(14, 12 - 3, 8);
    level.verticalBlock(15, 12 - 3, 8);
    level.nextPage(); //12
    
    level.pole(8, 2);
    level.castle(12, 2);
    level.resetPageIndex();
    
    level.nextPage();
    level.koopa(1, 4, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.lakitu(5, 11);
    level.koopa(9, 10, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.skipToPage(3);
    level.koopa(9, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.koopa(2, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.koopa(5, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.koopa(12, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.koopa(15, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.buzzyBeetle(15, 2);
    level.nextPage();
    level.buzzyBeetle(9, 2);
    level.buzzyBeetle(11, 2);
    //setRoomChange 0x42:8
    level.nextPage();
    level.koopa(11, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.skipToPage(10);
    level.koopa(10, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.koopa(12, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.koopa(15, 4, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.goomba(8, 5);
    level.goomba(10, 7);
    level.buzzyBeetle(13, 2);
    level.nextPage();
    level.koopa(11, 7, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.finalize();
}
void createArea8_3(sp::P<sp::Scene> scene)
{
    //complement=2 index=21
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Fence);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.castle(0, 2);
    level.nextPage(); //0
    
    level.bullitTower(2, 12 - 9, 2);
    //set background1(7, 2)
    //set background1(15, 0)
    level.nextPage(); //1
    
    level.bullitTower(2, 12 - 8, 3);
    //set background1(4, 2)
    level.nextPage(); //2
    
    //set background1(2, 0)
    level.pipe(5, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(5, 12 - 7);
    level.horizontalBricks(12, 12 - 3, 6);
    level.horizontalBricks(12, 12 - 7, 8);
    level.nextPage(); //3
    
    level.questionBlock(2, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Upgrade);
    level.horizontalBricks(3, 12 - 3, 1);
    level.hole(5, 2);
    level.verticalBlock(7, 12 - 7, 4);
    level.verticalBlock(8, 12 - 8, 3);
    level.verticalBlock(9, 12 - 9, 2);
    level.verticalBlock(10, 12 - 10, 1);
    level.hole(11, 2);
    //set background1(14, 2)
    level.nextPage(); //4
    
    //set background1(4, 0)
    level.bullitTower(6, 12 - 9, 2);
    //set background1(7, 2)
    //set background1(13, 0)
    level.verticalBlock(15, 12 - 8, 3);
    level.nextPage(); //5
    
    //set background1(0, 2)
    //set background1(10, 0)
    level.verticalBlock(13, 12 - 7, 4);
    level.verticalBlock(14, 12 - 7, 4);
    level.nextPage(); //6
    
    level.horizontalBricks(3, 12 - 3, 8);
    level.horizontalBricks(3, 12 - 7, 8);
    level.questionBlock(4, 12 - 3, QuestionBlock::Type::Brick, QuestionBlock::Contents::Upgrade);
    level.hole(12, 2);
    level.pipe(14, 12 - 7, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(14, 12 - 7);
    level.nextPage(); //7
    
    level.hole(0, 2);
    //set background1(3, 2)
    level.skipToPage(10);
    
    //set background1(5, 0)
    level.pipe(8, 12 - 8, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(8, 12 - 8);
    //set background1(11, 2)
    level.nextPage(); //10
    
    level.questionBlock(14, 12 - 7, QuestionBlock::Type::Brick, QuestionBlock::Contents::MultiCoin);
    //set background1(15, 0)
    level.nextPage(); //11
    
    level.verticalBlock(3, 12 - 9, 2);
    level.setBasic(4, 0);
    level.verticalBlock(6, 12 - 9, 1);
    level.verticalBlock(8, 12 - 7, 1);
    level.verticalBlock(10, 12 - 5, 1);
    level.horizontalBlock(12, 12 - 3, 2);
    level.setBasic(15, 1);
    level.nextPage(); //12
    
    level.pole(6, 2);
    //set background1(11, 2)
    level.largeCastle(12, 2);
    level.resetPageIndex();
    
    level.nextPage();
    level.koopa(14, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.skipToPage(3);
    level.hammerBrother(15, 2);
    level.nextPage();
    level.hammerBrother(1, 6);
    level.nextPage();
    level.koopa(13, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.skipToPage(7);
    level.hammerBrother(5, 6);
    level.hammerBrother(7, 2);
    level.nextPage();
    level.koopa(9, 2);
    level.nextPage();
    level.hammerBrother(2, 2);
    level.hammerBrother(15, 2);
    level.skipToPage(11);
    level.hammerBrother(1, 2);
    level.hammerBrother(9, 2);
    level.finalize();
}
void createArea8_4(sp::P<sp::Scene> scene)
{
    //complement=0 index=65
    global_area_data.start_position = sp::Vector2d(2, 8);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Castle, SmbLevelBuilder::Scenery::None);
    sp::Window::getInstance()->setClearColor(sp::Color(0, 0, 0));
    level.setBasic(-1, 4, 1);
    level.horizontalBlock(0, 12 - 5, 3);
    level.horizontalBlock(0, 12 - 6, 4);
    level.horizontalBlock(0, 12 - 7, 5);
    level.setBasic(5, 0, 1);
    level.setBasic(10, 1, 1);
    level.skipToPage(1);
    
    level.pipe(3, 12 - 9, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.skipToPage(3);
    
    level.pipe(3, 12 - 9, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    //enter pipe(3, 12 - 9);
    //loop-da-loop: 4
    level.setBasic(13, 4, 1);
    level.nextPage(); //3
    
    level.setBasic(1, 0, 1);
    level.setBasic(10, 4, 1);
    level.horizontalBlock(12, 12 - 4, 4);
    level.nextPage(); //4
    
    level.pipe(1, 12 - 6, 7, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(1, 12 - 6);
    //enter pipe(1, 12 - 6);
    level.pipe(10, 12 - 5, 8, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(10, 12 - 5);
    level.setBasic(15, 1, 1);
    level.nextPage(); //5
    
    level.setBasic(15, 1, 1);
    level.skipToPage(7);
    
    level.pipe(3, 12 - 9, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.pipe(10, 12 - 8, 5, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(10, 12 - 8);
    //loop-da-loop: 14
    level.nextPage(); //7
    
    level.pipe(4, 12 - 9, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(4, 12 - 9);
    //enter pipe(4, 12 - 9);
    level.pipe(14, 12 - 8, 5, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(14, 12 - 8);
    level.setBasic(15, 0, 1);
    level.nextPage(); //8
    
    level.setBasic(2, 1, 1);
    level.questionBlock(6, 12 - 7, QuestionBlock::Type::Hidden);
    level.pipe(8, 12 - 4, 3, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(8, 12 - 4);
    //enter pipe(8, 12 - 4);
    level.horizontalBlock(8, 12 - 7, 2);
    level.skipToPage(11);
    
    level.setBasic(15, 1, 1);
    level.skipToPage(12);
    
    level.pipe(3, 12 - 9, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.setBasic(5, 4, 1);
    level.pipe(12, 12 - 6, 7, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(12, 12 - 6);
    level.nextPage(); //12
    
    level.pipe(4, 12 - 5, 8, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(4, 12 - 5);
    //enter pipe(4, 12 - 5);
    level.setBasic(11, 0, 1);
    level.startCheepCheepJumping(7);
    level.setBasic(15, 4, 1);
    level.nextPage(); //13
    
    //loop-da-loop: 3
    level.pipe(4, 12 - 6, 7, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(4, 12 - 6);
    //enter pipe(4, 12 - 6);
    level.stopContinuousGeneration(4);
    level.nextPage(); //14
    
    level.setBasic(15, 1, 1);
    level.nextPage(); //15
    
    level.pipe(3, 12 - 9, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.pipe(10, 12 - 9, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(10, 12 - 9);
    //enter pipe(10, 12 - 9);
    level.nextPage(); //16
    
    level.setBasic(4, 0, 1);
    level.setBasic(9, 4, 3);
    level.setBasic(15, 0, 1);
    level.nextPage(); //17
    
    level.castleBridge(0, 4, 13);
    level.bridgeRope(12, 5);
    level.setBasic(12, 5, 1);
    level.setBasic(13, 5, 4);
    level.bridgeAxe(13, 6);
    level.setBasic(15, 1, 1);
    level.nextPage(); //18
    
    level.setScrollStop(-1);
    level.resetPageIndex();
    
    level.skipToPage(3);
    //setRoomChange 0x65:1
    level.goomba3(8, 2);
    level.nextPage();
    level.lift(6, 1, Lift::Type::LeftRight, Lift::Size::Small);
    level.nextPage();
    //setRoomChange 0xe5:7
    level.skipToPage(8);
    level.buzzyBeetle(0, 2);
    level.buzzyBeetle(2, 2);
    //setRoomChange 0x65:1
    level.koopa(11, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.koopa(13, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.nextPage();
    level.koopa(11, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    level.koopa(13, 2, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping);
    //setRoomChange 0x65:12
    level.skipToPage(13);
    //setRoomChange 0x65:1
    level.skipToPage(14);
    //setRoomChange 0x2:0
    level.skipToPage(16);
    //setRoomChange 0x65:1
    level.nextPage();
    level.hammerBrother(1, 2);
    level.podoboo(7, 2);
    level.nextPage();
    level.startBowserFire(5);
    level.bowser(7, 5);
    level.nextPage();
    level.princess(9, 2);
    level.finalize();
}
void createArea10_0(sp::P<sp::Scene> scene)
{
    //complement=0 index=00
    global_area_data.start_position = sp::Vector2d(2, 13);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Water, SmbLevelBuilder::Scenery::None);
    sp::Window::getInstance()->setClearColor(sp::Color(66/255.0f, 66/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.horizontalBlock(11, 12 - 4, 5);
    level.verticalSeaplant(12, 12 - 8, 3);
    level.verticalSeaplant(15, 12 - 2, 2);
    level.nextPage(); //0
    
    level.verticalSeaplant(4, 12 - 7, 4);
    level.hole(6, 4);
    level.coins(6, 12 - 5, 10);
    level.setBasic(9, 4, 3);
    level.setBasic(11, 1);
    level.hole(12, 4);
    level.setBasic(15, 4, 3);
    level.nextPage(); //1
    
    level.startUnderwaterCheepCheeps(-6);
    level.setBasic(1, 1);
    level.hole(6, 2);
    level.horizontalBlock(6, 12 - 2, 6);
    level.verticalSeaplant(6, 12 - 3, 4);
    level.coins(8, 12 - 10, 2);
    level.hole(10, 2);
    level.verticalSeaplant(11, 12 - 3, 4);
    level.verticalSeaplant(14, 12 - 9, 2);
    level.nextPage(); //2
    
    level.coins(2, 12 - 6, 4);
    level.horizontalBlock(2, 12 - 7, 4);
    level.coins(6, 12 - 3, 4);
    level.horizontalBlock(6, 12 - 4, 4);
    level.verticalBlock(11, 12 - 10, 1);
    level.verticalBlock(12, 12 - 9, 2);
    level.setBasic(12, 5, 4);
    level.setBasic(13, SmbLevelBuilder::AllBricks);
    level.sidePipeEntrance(14, 12 - 5, SmbLevelBuilder::PipeColor::Green);
    (new PipeEntrance(scene->getRoot(), PipeEntrance::Type::Left, [](){
        createFinish(sp::Scene::get("stage"));
    }))->setPosition(sp::Vector2d(level.getPageIndex() * 16 + 14.5, 7));
    level.nextPage(); //3
    
    level.stopContinuousGeneration(1);
    level.setScrollStop(1);
    level.resetPageIndex();
    
    level.nextPage();
    level.blooper(3, 2);
    level.lift(6, 8, Lift::Type::Down, Lift::Size::Small);
    level.lift(12, 2, Lift::Type::Down, Lift::Size::Small);
    level.nextPage();
    level.blooper(3, 2);
    level.blooper(13, 2);
    level.finalize();
}
void createArea10_1(sp::P<sp::Scene> scene)
{
    //complement=0 index=02
    global_area_data.start_position = sp::Vector2d(2, 13);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Water, SmbLevelBuilder::Scenery::None);
    sp::Window::getInstance()->setClearColor(sp::Color(66/255.0f, 66/255.0f, 255/255.0f));
    level.setBasic(-1, SmbLevelBuilder::AllBricks);
    level.setBasic(1, 1);
    level.pipe(3, 12 - 9, 4, SmbLevelBuilder::PipeColor::Green);
    level.piranhaPlant(3, 12 - 9);
    level.setBasic(5, 4, 3);
    level.setBasic(10, 5, 4);
    level.nextPage(); //0
    
    level.setBasic(1, 1, 1);
    level.nextPage(); //1
    
    level.setBasic(6, 4, 4);
    level.setBasic(9, 1, 1);
    level.skipToPage(4);
    
    level.setBasic(2, 5, 4);
    level.setBasic(3, SmbLevelBuilder::AllBricks);
    level.sidePipeEntrance(4, 12 - 5, SmbLevelBuilder::PipeColor::Green);
    (new PipeEntrance(scene->getRoot(), PipeEntrance::Type::Left, [](){
        createFinish(sp::Scene::get("stage"));
    }))->setPosition(sp::Vector2d(level.getPageIndex() * 16 + 4.5, 7));
    level.setScrollStop(8);
    level.resetPageIndex();
    
    level.nextPage();
    level.fireBar(4, 7, FireBar::Type::Right);
    level.blooper(12, 2);
    level.fireBar(15, 4, FireBar::Type::Left);
    level.nextPage();
    level.fireBar(8, 8, FireBar::Type::Right);
    level.nextPage();
    level.blooper(3, 3);
    level.blooper(5, 7);
    level.fireBar(8, 6, FireBar::Type::Right);
    level.nextPage();
    level.fireBar(0, 7, FireBar::Type::Left);
    level.finalize();
}
void createArea10_2(sp::P<sp::Scene> scene)
{
    //complement=3 index=2b
    global_area_data.start_position = sp::Vector2d(2, 13);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::None);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.hole(4, 1);
    level.coins(15, 12 - 4, 16);
    level.skipToPage(2);
    
    level.coins(0, 12 - 2, 3);
    level.coins(4, 12 - 3, 16);
    level.nextPage(); //2
    
    level.coins(5, 12 - 2, 3);
    level.setBasic(13, 0);
    level.nextPage(); //3
    
    level.coins(5, 12 - 10, 3);
    level.nextPage(); //4
    
    level.setScrollStop(-2);
    level.resetPageIndex();
    
    level.nextPage();
    level.lift(0, 4, Lift::Type::Surfing, Lift::Size::Small);
    level.finalize();
}
void createArea10_3(sp::P<sp::Scene> scene)
{
    //complement=1 index=2f
    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Clouds);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.hole(4, 1);
    level.mushroomIsland(12, 12 - 7, 3);
    level.coins(12, 12 - 6, 3);
    level.nextPage(); //0
    
    level.mushroomIsland(0, 12 - 3, 3);
    level.coins(0, 12 - 2, 3);
    level.mushroomIsland(2, 12 - 9, 3);
    level.mushroomIsland(6, 12 - 3, 3);
    level.coins(6, 12 - 2, 3);
    level.mushroomIsland(6, 12 - 9, 5);
    level.mushroomIsland(10, 12 - 5, 3);
    level.coins(10, 12 - 4, 3);
    level.mushroomIsland(14, 12 - 2, 5);
    level.coins(14, 12 - 1, 5);
    level.mushroomIsland(15, 12 - 8, 7);
    level.nextPage(); //1
    
    level.coins(3, 12 - 7, 2);
    level.stairs(8, 2, 8);
    level.verticalBlock(16, 12 - 3, 8);
    level.nextPage(); //2
    
    level.horizontalBlock(0, 12 - 2, 12);
    level.pipe(2, 12 - 8, 3, SmbLevelBuilder::PipeColor::Red);
    level.piranhaPlant(2, 12 - 8);
    //enter pipe(2, 12 - 8);
    level.pipe(6, 12 - 8, 3, SmbLevelBuilder::PipeColor::Red);
    level.piranhaPlant(6, 12 - 8);
    //enter pipe(6, 12 - 8);
    level.pipe(10, 12 - 8, 3, SmbLevelBuilder::PipeColor::Red);
    level.piranhaPlant(10, 12 - 8);
    //enter pipe(10, 12 - 8);
    level.verticalBlock(14, 12 - 0, 11);
    level.verticalBlock(15, 12 - 0, 11);
    level.nextPage(); //3
    
    level.setScrollStop(0); //warpzone
    level.resetPageIndex();
    
    level.finalize();
}
void createArea10_4(sp::P<sp::Scene> scene)
{
    //complement=3 index=34
    global_area_data.start_position = sp::Vector2d(2, 13);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::None);
    //night & snow (TODO: Snow)
    sp::Window::getInstance()->setClearColor(sp::Color(0.1, 0.1, 0.1));
    level.setBasic(-1, 1);
    level.hole(4, 1);
    level.coins(15, 12 - 4, 16);
    level.skipToPage(2);
    
    level.horizontalBricks(0, 12 - 6, 1);
    level.coins(2, 12 - 4, 16);
    level.nextPage(); //2
    
    level.horizontalBricks(3, 12 - 5, 1);
    level.horizontalBricks(3, 12 - 6, 1);
    level.coins(5, 12 - 3, 7);
    level.horizontalBricks(13, 12 - 5, 1);
    level.horizontalBricks(13, 12 - 6, 1);
    level.nextPage(); //3
    
    level.horizontalBricks(3, 12 - 4, 2);
    level.coins(7, 12 - 3, 10);
    level.horizontalBricks(7, 12 - 4, 1);
    level.horizontalBricks(9, 12 - 4, 1);
    level.horizontalBricks(11, 12 - 4, 1);
    level.horizontalBricks(13, 12 - 4, 1);
    level.horizontalBricks(15, 12 - 4, 1);
    level.nextPage(); //4
    
    level.setBasic(2, 0);
    level.coins(5, 12 - 9, 3);
    level.nextPage(); //5
    
    level.setScrollStop(-2);
    level.resetPageIndex();
    
    level.nextPage();
    level.lift(0, 4, Lift::Type::Surfing, Lift::Size::Small);
    level.finalize();
}
void createArea10_5(sp::P<sp::Scene> scene)
{
    //complement=0 index=42
    global_area_data.start_position = sp::Vector2d(2, 13);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Underground, SmbLevelBuilder::Scenery::None);
    sp::Window::getInstance()->setClearColor(sp::Color(0, 0, 0));
    level.setBasic(-1, 1);
    level.setBasic(0, 1);
    level.verticalBricks(0, 12 - 0, 11);
    level.setBasic(3, 4, 1);
    level.coins(4, 12 - 5, 7);
    level.coins(4, 12 - 7, 7);
    level.coins(5, 12 - 3, 5);
    level.setBasic(10, 1);
    level.reverseLPipe(13, 12 - 10, 2, 10, SmbLevelBuilder::PipeColor::Green);
    (new PipeEntrance(scene->getRoot(), PipeEntrance::Type::Left, [](){
    }))->setPosition(sp::Vector2d(level.getPageIndex() * 16 + 13.5, 6));
    level.nextPage(); //0
    
    level.setScrollStop(-2);
    level.nextPage(); //1
    
    level.setBasic(0, 1);
    level.verticalBricks(0, 12 - 0, 11);
    level.setBasic(2, 1, 4);
    level.horizontalBricks(3, 12 - 7, 9);
    level.coins(3, 12 - 10, 9);
    level.coins(4, 12 - 6, 8);
    level.questionBlock(12, 12 - 7, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::MultiCoin);
    level.setBasic(12, SmbLevelBuilder::AllBricks);
    level.reverseLPipe(13, 12 - 10, 2, 10, SmbLevelBuilder::PipeColor::Green);
    (new PipeEntrance(scene->getRoot(), PipeEntrance::Type::Left, [](){
    }))->setPosition(sp::Vector2d(level.getPageIndex() * 16 + 13.5, 6));
    level.nextPage(); //2
    
    level.setScrollStop(-2);
    level.nextPage(); //3
    
    level.setBasic(0, 1);
    level.verticalBricks(0, 12 - 0, 11);
    level.verticalBricks(3, 12 - 3, 4);
    level.verticalBricks(4, 12 - 3, 2);
    level.coins(4, 12 - 6, 1);
    level.verticalBricks(4, 12 - 7, 1);
    level.questionBlock(5, 12 - 3, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::Upgrade);
    level.coins(5, 12 - 5, 1);
    level.verticalBricks(5, 12 - 6, 1);
    level.coins(6, 12 - 2, 4);
    level.coins(6, 12 - 4, 1);
    level.verticalBricks(6, 12 - 5, 1);
    level.coins(7, 12 - 1, 2);
    level.verticalBricks(7, 12 - 3, 2);
    level.verticalBricks(8, 12 - 3, 2);
    level.coins(9, 12 - 4, 1);
    level.verticalBricks(9, 12 - 5, 1);
    level.verticalBricks(10, 12 - 3, 1);
    level.coins(10, 12 - 5, 1);
    level.verticalBricks(10, 12 - 6, 1);
    level.verticalBricks(11, 12 - 3, 2);
    level.coins(11, 12 - 6, 1);
    level.verticalBricks(11, 12 - 7, 1);
    level.verticalBricks(12, 12 - 3, 4);
    level.reverseLPipe(13, 12 - 10, 2, 10, SmbLevelBuilder::PipeColor::Green);
    (new PipeEntrance(scene->getRoot(), PipeEntrance::Type::Left, [](){
    }))->setPosition(sp::Vector2d(level.getPageIndex() * 16 + 13.5, 6));
    level.nextPage(); //4
    
    level.setScrollStop(-2);
    level.nextPage(); //5
    
    level.setBasic(0, 1);
    level.verticalBricks(0, 12 - 0, 11);
    level.setBasic(2, 1, 1);
    level.coins(3, 12 - 6, 8);
    level.verticalBricks(3, 12 - 7, 3);
    level.coins(3, 12 - 10, 10);
    level.horizontalBricks(4, 12 - 7, 6);
    level.verticalBricks(10, 12 - 7, 3);
    level.questionBlock(13, 12 - 7, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::Upgrade);
    level.reverseLPipe(13, 12 - 10, 2, 10, SmbLevelBuilder::PipeColor::Green);
    (new PipeEntrance(scene->getRoot(), PipeEntrance::Type::Left, [](){
    }))->setPosition(sp::Vector2d(level.getPageIndex() * 16 + 13.5, 6));
    level.nextPage(); //6
    
    level.setScrollStop(-2);
    level.nextPage(); //7
    
    level.setBasic(0, 1);
    level.verticalBricks(0, 12 - 0, 11);
    level.setBasic(3, 1, 1);
    level.verticalBricks(4, 12 - 4, 2);
    level.coins(5, 12 - 3, 5);
    level.coins(5, 12 - 4, 5);
    level.horizontalBricks(5, 12 - 5, 5);
    level.verticalBricks(10, 12 - 1, 5);
    level.setBasic(10, 1);
    level.horizontalBricks(11, 12 - 4, 2);
    level.reverseLPipe(13, 12 - 10, 2, 10, SmbLevelBuilder::PipeColor::Green);
    (new PipeEntrance(scene->getRoot(), PipeEntrance::Type::Left, [](){
    }))->setPosition(sp::Vector2d(level.getPageIndex() * 16 + 13.5, 6));
    level.questionBlock(14, 12 - 5, QuestionBlock::Type::BrickUnderground, QuestionBlock::Contents::MultiCoin);
    level.nextPage(); //8
    
    level.setScrollStop(-2);
    level.resetPageIndex();
    
    level.nextPage();
    level.skipToPage(3);
    level.skipToPage(5);
    level.skipToPage(7);
    level.skipToPage(9);
    level.finalize();
}
void createFinish(sp::P<sp::Scene> scene)
{
    global_area_data.start_position = sp::Vector2d(1.5, 4);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Clouds);
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    level.setBasic(-1, 1);
    level.pipe(1, 12 - 9, 2);
    level.stairs(3, 2, 8);
    level.verticalBlock(11, 12 - 3, 8);
    level.nextPage();
    
    level.pole(4, 2);
    level.castle(8, 2);
    level.resetPageIndex();
    level.finalize();
}
