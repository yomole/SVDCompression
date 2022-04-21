#include "ImageViewer.h"

void showImage(const string& fileLocation){
    //1. Check if the file exists and is a valid image file.
    if (fs::exists(fileLocation) && AssetManager::validFile(fileLocation)){
        //2. Alert the user that the image will be displayed and they will be required to close window.
        cout << "Displaying " << fileLocation << "." << endl << "Close the window to continue..." << endl;
        //3. Load texture, assign to sprite, and generate scaling factor for sprite.
        Texture image;
        image.loadFromFile(fileLocation);
        Sprite dispImage(image);
        float scaleX = ((float)sf::VideoMode::getDesktopMode().width / VIDEOMODE_SCALE) / (float)image.getSize().x;
        float scaleY = ((float)sf::VideoMode::getDesktopMode().height / VIDEOMODE_SCALE) / (float)image.getSize().y;

        Vector2f scales;

        //5. Use the smaller of the two possible scaling factors (in case longer than tall or vice versa).
        if (scaleX < scaleY){
            scales.x = scaleX;
            scales.y = scaleX;
        }

        else{
            scales.x = scaleY;
            scales.y = scaleY;
        }

        //6. Set scale and display image.
        dispImage.setScale(scales);
        sf::RenderWindow window(sf::VideoMode(dispImage.getGlobalBounds().width, dispImage.getGlobalBounds().height),
                                "Media Compression by iCompression ~ show " + fileLocation, sf::Style::Close);

        if (!AssetManager::isLoaded()){
            AssetManager("");
        }

        while(window.isOpen()) {
            Event event{};
            while (window.pollEvent(event)) {

                if (event.type == Event::Closed) {
                    window.close();
                }
                window.draw(dispImage);
                window.display();
            }
        }
    }

    else{
        cerr << "File " << fileLocation << " does not exist or isn't valid, so the image cannot be displayed." << endl;
    }
}

void showImages(){

    if (AssetManager::getFiles().empty()){
        cerr << "No files were loaded into the program!" << endl;
        return;
    }

    if (AssetManager::getCompressedFiles().empty()){
        cerr << "No files were compressed by the program!" << endl;
        return;
    }

    //3. Create the window and scene manager. Add the scene and change to it.
    sf::RenderWindow window(sf::VideoMode(0, 0),
                            "Media Compression by iCompression: Qualitative Comparison", sf::Style::Close);
    window.setFramerateLimit(60);

    if (!AssetManager::isLoaded()){
        AssetManager("");
    }

    SceneManager sceneManager(&window);
    SceneManager::addScene("Images");
    SceneManager::changeScene("Images");

    //4. Load all of the images.
    auto& originalSet = AssetManager::getFiles();
    auto& compressedSet = AssetManager::getCompressedFiles();

    auto originalImages = originalSet.begin();
    auto compressedImages = compressedSet.begin();

    for (auto& file : originalSet){
        if (!AssetManager::textureExists(file)){
            AssetManager::addImage(AssetManager::getPrefix() + file);
        }
    }

    for (auto& file : compressedSet){
        if (!AssetManager::textureExists(file)){
            AssetManager::addImage(AssetManager::getPrefix() + file);
        }
    }

    //4. Create the buttons, sprites, and text to be moved later.
    auto& scene = SceneManager::getScene("Images");
    scene.addImage("original", *originalImages, Vector2f(0,0));
    scene.addImage("compressed", *originalImages, Vector2f(0,0));
    scene.addText("fn", Vector2f(0,0), AssetManager::getFont(DEFAULT_FONT.data()), 20, "File: []");
    scene.addText("fsOrig", Vector2f(0,0), AssetManager::getFont(DEFAULT_FONT.data()), 20, "Original Size: []");
    scene.addText("fsSVD", Vector2f(0,0), AssetManager::getFont(DEFAULT_FONT.data()), 20, "SVD Size: []");
    scene.addText("fsHuffman", Vector2f(0,0), AssetManager::getFont(DEFAULT_FONT.data()), 20, "Huffman Size: []");

    auto& original = scene.getImages("original");
    auto& compressed = scene.getImages("compressed");

    scene.addButton("forward", "Forward.png", Vector2f(0,0), [&originalImages, &compressedImages, &originalSet,
            &compressedSet, &original, &compressed, &window, &scene]()->void {
        //Check if the iterator will reach the end, and reset to the beginning if true.
        originalImages++;
        compressedImages++;
        if (originalImages == originalSet.end()) {
            originalImages = originalSet.begin();
            compressedImages = compressedSet.begin();
        }

        //Get the next textures.
        const Texture &originalNext = AssetManager::getTexture(fs::path(*originalImages).filename().string());
        const Texture &compressedNext = AssetManager::getTexture(fs::path(*compressedImages).filename().string());

        //Set the images textures to the next textures.
        original->setTexture(originalNext, true);
        compressed->setTexture(compressedNext, true);

        //Set the filesizes and filename to the approprite ones.
        updateText(*originalImages, *compressedImages, scene);

        //Adjust the window to fit the new images.
        adjustWindow(window, scene);
    });

    scene.addButton("reverse", "Reverse.png", Vector2f(0,0), [&originalImages, &compressedImages, &originalSet,
            &compressedSet, &original, &compressed, &window, &scene]()->void {
        //Check if the iterator is at the beginning. If so, wrap around to the end - 1.
        originalImages--;
        compressedImages--;
        if (originalImages == originalSet.begin()) {
            originalImages = --originalSet.end();
            compressedImages = --compressedSet.end();
        }

        //Get the previous textures.
        const Texture &originalPrev = AssetManager::getTexture(fs::path(*originalImages).filename().string());
        const Texture &compressedPrev = AssetManager::getTexture(fs::path(*compressedImages).filename().string());

        //Set the images textures to the previous textures.
        original->setTexture(originalPrev, true);
        compressed->setTexture(compressedPrev, true);

        //Set the filesizes and filename to the approprite ones.
        updateText(*originalImages, *compressedImages, scene);

        //Adjust the window to fit the new images.
        adjustWindow(window, scene);
    });

    auto& forward = scene.getButtons("forward");
    auto& reverse = scene.getButtons("reverse");

    //Adjust the window and text first before opening it.
    adjustWindow(window, scene);
    updateText(*originalImages, *compressedImages, scene);

    //Alert the user that the images will be displayed and they will be required to close window.
    cout << "Displaying compressed images." << endl << "Close the window to continue..." << endl;

    while(window.isOpen()) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            else if (event.type == Event::MouseButtonPressed){
                if (event.mouseButton.button == Mouse::Left){
                    SceneManager::activateElement(Mouse::getPosition(window));
                }
            }

            window.clear(Color::White);
            SceneManager::drawAll();
            window.display();
        }
    }
}

void updateText(const string& origFile, const string& compFile, Scene& scene){
    //1. Grab the pointers.
    unique_ptr<Text>& fn = scene.getTexts("fn");
    unique_ptr<Text>& fsOrig = scene.getTexts("fsOrig");
    unique_ptr<Text>& fsSVD = scene.getTexts("fsSVD");
    unique_ptr<Text>& fsHuffman = scene.getTexts("fsHuffman");

    //2. Update the text.
    //TODO: Replace with actual Huffman size when available.
    const auto& fnNew = fs::path(origFile).filename().string();
    string path = fs::path(AssetManager::getOutputFolder() + "svd/bin/" + fnNew).string();
    path.replace(path.find_last_of('.'), 4, ".bin");

    const auto& fsOrigNew = (float)file_size(fs::path(origFile)) / (float)1024;
    const auto& fsSVDNew = (float)file_size(fs::path(path)) / (float)1024;

    string huffmanName =  AssetManager::getOutputFolder() + "huffman/bin/" + fs::path(origFile).filename().string();
    huffmanName.replace(huffmanName.find_last_of('.'), 4, ".bin");
    const auto fsHuffmanNew = file_size(fs::path(huffmanName)) / (float)1024;

    fn->setString("File: " + fnNew);
    fsOrig->setString("Original File Size: " + to_string(fsOrigNew) + " Kb");
    fsSVD->setString("SVD File Size: " + to_string(fsSVDNew) + " Kb");
    fsHuffman->setString("Huffman File Size: " + to_string(fsHuffmanNew) + " Kb");
}

void adjustWindow(sf::RenderWindow& window, Scene& scene){
    unique_ptr<Sprite>& original = scene.getImages("original");
    unique_ptr<Sprite>& compressed = scene.getImages("compressed");
    unique_ptr<Button>& forward = scene.getButtons("forward");
    unique_ptr<Button>& reverse = scene.getButtons("reverse");
    unique_ptr<Text>& fn = scene.getTexts("fn");
    unique_ptr<Text>& fsOrig = scene.getTexts("fsOrig");
    unique_ptr<Text>& fsSVD = scene.getTexts("fsSVD");
    unique_ptr<Text>& fsHuffman = scene.getTexts("fsHuffman");

    //1. Get the images and their size.
    sf::Vector2u size2u = original->getTexture()->getSize();

    //2. Generate the scaling factor for the images.
    float scaleX = ((float)sf::VideoMode::getDesktopMode().width / VIDEOMODE_SCALE) / (float)size2u.x;
    float scaleY = ((float)sf::VideoMode::getDesktopMode().height / VIDEOMODE_SCALE) / (float)size2u.y;

    //3. Use the smaller of the two.
    Vector2f scales;
    scales = (scaleX < scaleY ? Vector2f(scaleX, scaleX) : Vector2f(scaleY, scaleY));
    original->setScale(scales);
    compressed->setScale(scales);

    //4. Resize the window to fit both images, buttons, and text with margins.
    Vector2u buttonSize = forward->getBaseTexture().getSize();
    unsigned int imageWidth = original->getGlobalBounds().width;
    unsigned int imageHeight = original->getGlobalBounds().height;
    auto filenameHeight = fn->getGlobalBounds().height;

    unsigned int width = (imageWidth * 2) + (3 * IMAGE_MARGIN);
    unsigned int height = imageHeight + (2 * IMAGE_MARGIN) + buttonSize.x + (2 * filenameHeight);


    Vector2u newSize(width, height);
    window.setSize(newSize);
    window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)));
    window.setPosition(sf::Vector2i(0,0));

    //5. Reposition the elements.
    original->setPosition(Vector2f(IMAGE_MARGIN, IMAGE_MARGIN));
    compressed->setPosition(Vector2f(((2 * IMAGE_MARGIN) + imageWidth), IMAGE_MARGIN));
    reverse->getSprite().setPosition(Vector2f(IMAGE_MARGIN, (2 * IMAGE_MARGIN) + imageHeight));
    forward->getSprite().setPosition(Vector2f((2 * IMAGE_MARGIN) + buttonSize.x, (2 * IMAGE_MARGIN) + imageHeight));
    fn->setPosition(Vector2f(forward->getSprite().getPosition().x + buttonSize.x + IMAGE_MARGIN
                                   , forward->getSprite().getPosition().y));

    auto filenamePos = fn->getPosition();
    fsOrig->setPosition(Vector2f(filenamePos.x, filenamePos.y + filenameHeight));
    fsSVD->setPosition(Vector2f(filenamePos.x, filenamePos.y + (2 * filenameHeight)));
    fsHuffman->setPosition(Vector2f(filenamePos.x, filenamePos.y + (3 * filenameHeight)));
}