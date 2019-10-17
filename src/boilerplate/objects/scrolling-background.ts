/*
 * Глобальный менеджер фонов
 */
export class ScrollingBackground {
    private scene;
    private sprites = [];
    private velocityY;
    private layers;

    //TODO нужен расчёт скорости на основе количества спрайтов
    constructor(scene: Phaser.Scene, sprites, velocityY: integer = 10) {
        this.scene = scene;
        for (let i = 0; i < sprites.length; i++) {
            this.sprites.push({
                sprite: sprites[i],
                tileY: false
            });
        }
        this.velocityY = velocityY;

        this.createLayers();
    }

    setScene(scene: Phaser.Scene): void {
        //TODO добавить тряску камеры как визуальный отклик
        this.scene = scene;
        this.createLayers();
    }

    createLayers(): void {
        this.layers = this.scene.add.group();

        for (let i = 0; i < this.sprites.length; i++) {
            let sprite = this.sprites[i];
            let layer = this.scene.add.tileSprite(
                this.scene.cameras.main.width / 2,
                this.scene.cameras.main.height / 2,
                this.scene.cameras.main.width,
                this.scene.cameras.main.height,
                sprite.sprite);
            layer.setScale(2, 2);
            layer.setDepth(-5 - (i - 1));

            this.layers.add(layer);
            if (sprite.tileY !== false) {
                layer.tilePositionY = sprite.tileY;
            }
        }
    }

    update(): void {
        for (let i = 0; i < this.layers.getChildren().length; i++) {
            let layer = this.layers.getChildren()[i];
            let speed = i > 0 ? this.velocityY * (i + 1) * 0.1 : this.velocityY * 0.1;
            layer.tilePositionY -= speed;
            this.sprites[i].tileY = layer.tilePositionY;
        }
    }
}