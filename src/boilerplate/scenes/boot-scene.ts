export class BootScene extends Phaser.Scene {
    private loadingBar: Phaser.GameObjects.Graphics;
    private progressBar: Phaser.GameObjects.Graphics;
    private loadingScreen: Phaser.GameObjects.Image;

    constructor() {
        super({
            key: "BootScene"
        });
    }

    preload(): void {
        // set the background and create loading bar
        this.cameras.main.setBackgroundColor(0x410B21);
        this.createLoadingBar();

        // pass value to change the loading bar fill
        this.load.on(
            "progress",
            function(value) {
                this.progressBar.clear();
                this.progressBar.fillStyle(0x9D1A50, 1);
                this.progressBar.fillRect(
                    0,
                    this.cameras.main.height - 7,
                    this.cameras.main.width * value,
                    6
                );
            },
            this
        );

        // delete bar graphics, when loading complete
        this.load.on(
            "complete",
            function() {
                // this.progressBar.destroy();
                // this.loadingBar.destroy();
            },
            this
        );

        // load out package
        this.load.pack(
            "preload",
            "./src/boilerplate/assets/pack.json",
            "preload"
        );
    }

    update(): void {
        // this.scene.start("MainMenuScene");
        // this.scene.start("CombatScene");
    }

    private createLoadingBar(): void {
        this.loadingBar = this.add.graphics();
        this.loadingBar.fillStyle(0xC32F69, 1);
        this.loadingBar.fillRect(
            0,
            this.cameras.main.height - 8,
            this.cameras.main.width + 4,
            10
        );
        this.progressBar = this.add.graphics();
    }
}
