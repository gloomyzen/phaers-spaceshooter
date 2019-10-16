import { ScrollingBackground } from "../objects/scrolling-background";

export class MainMenuScene extends Phaser.Scene {
    private titleBitmapText: Phaser.GameObjects.BitmapText;
    private title: Phaser.GameObjects.Text;
    private btnPlay: Phaser.GameObjects.Sprite;
    private sfx;
    private backgrounds: ScrollingBackground;

    constructor() {
        super({
            key: "MainMenuScene"
        });
    }

    create(): void {
        this.titleBitmapText = this.add.bitmapText(
            0,
            200,
            "font",
            this.game.config.gameTitle.toUpperCase(),
            30
        );

        this.titleBitmapText.x = this.getCenterXPositionOfBitmapText(
            this.titleBitmapText.width
        );


        this.sfx = {
            mainTheme: this.sound.add("sndMainTheme"),
            btnOver: this.sound.add("sndBtnOver"),
            btnDown: this.sound.add("sndBtnDown")
        };
        //start main theme sound
        // todo uncomment after testing
        // this.sfx.mainTheme.play();

        //button init and animation
        this.btnPlay = this.add.sprite(
            this.cameras.main.width * 0.5,
            this.cameras.main.height * 0.5,
            "sprBtnPlay"
        );
        this.btnPlay.setInteractive();
        this.btnPlay.on("pointerover", function() {
            this.btnPlay.setTexture("sprBtnPlayHover");
            this.sfx.btnOver.play();
        }, this);
        this.btnPlay.on("pointerout", function() {
            this.setTexture("sprBtnPlay");
        });
        this.btnPlay.on("pointerdown", function() {
            this.btnPlay.setTexture("sprBtnPlayDown");
            this.sfx.btnDown.play();
        }, this);
        this.btnPlay.on("pointerup", function() {
            this.btnPlay.setTexture("sprBtnPlay");
            console.log('start scene: CombatScene');
            this.scene.start("CombatScene");
        }, this);

        let gameTitle = this.game.config.gameTitle + " v" + this.game.config.gameVersion + " " + this.game.config.gameURL;
        this.title = this.add.text(
            5,
            5,
            gameTitle.toUpperCase(),
            {
                fontFamily: 'monospace',
                fontSize: 12,
                fontStyle: 'bold',
                color: '#ffffff',
                align: 'left'
            });

        // space background
        this.backgrounds = new ScrollingBackground(this, ["sprBg0", "sprBg1"]);
    }

    update(): void {
        this.backgrounds.update();
    }

    private getCenterXPositionOfBitmapText(width: number): number {
        return this.sys.canvas.width / 2 - width / 2;
    }
}
