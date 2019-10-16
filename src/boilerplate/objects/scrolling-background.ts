export class ScrollingBackground {
    private scene;
    private keys;
    private velocityY;
    private layers;

    constructor(scene: Phaser.Scene, keys, velocityY: integer = 10) {
        this.scene = scene;
        this.keys = keys;
        this.velocityY = velocityY;

        this.layers = this.scene.add.group();
        this.createLayers();
    }

    createLayers(): void {
        for (let i = 0; i < this.keys.length; i++) {
            let key = this.keys[i];
            let layer = this.scene.add.tileSprite(
                this.scene.cameras.main.width / 2,
                this.scene.cameras.main.height / 2,
                this.scene.cameras.main.width,
                this.scene.cameras.main.height,
                key);
            layer.setScale(2, 2);
            layer.setDepth(-5 - (i - 1));
            // this.scene.physics.world.enableBody(layer, 0);
            // layer.body.velocity.y = this.velocityY;
            this.layers.add(layer);
        }
    }

    update(): void {
        for (let i = 0; i < this.layers.getChildren().length; i++) {
            let layer = this.layers.getChildren()[i];
            let speed = i > 0 ? this.velocityY * (i + 1) * 0.1 : this.velocityY * 0.1;
            layer.tilePositionY -= speed;
        }
    }
}