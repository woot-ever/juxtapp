class CRunner {
public:
	// *(_DWORD *)a1 = &_vtable_for_CRunner[2];
	// *(_DWORD *)(a1 + 188) = &_vtable_for_CRunner[68];
	// *(_DWORD *)(a1 + 64) = &_vtable_for_CRunner[53];
	
	char inherited[488];
	
    int last_hitter; // 488
    Vec2f last_hitpoint; // 492
    float last_hitpower; // 500 - its ok
    unsigned int sprite; //  504  - its ok
    int tilesize; // 508
    float scale; // 512
    char tool; // 516 - its ok
	
	// ------ edited 
	char gowno1;
	char gowno2;
	char gowno3;
	// ------ edited 
	
    int build; // 520
    int old_build; // 524
    int face; //  528
    int idletime; // 532
    int hitcount; // 536
    int hittime; // 540
    int default_hitcount; // 544
    int strikecount; // 548
    int striketime; // 552
    int drawtime; // 556
    int knockdown; // 560
    int oldknockdown; // 564
    bool strikeup; // 568
    int strikekind; // 572
    int slashlimiter; // 574
    int runanim_time; // 580
    int glideanim_time; // 584
    int weapon; // 588
    int old_weapon; // 592
    irr::core::vector3df translation; // 596
    irr::core::vector3df rotation; // 608
    Vec2f pos; // 620 - its ok
    Vec2f oldpos; // 628
    Vec2f drawpos; // 636
    Vec2f vel; // 644
    Vec2f oldvel; // 652
    Vec2f colvel; // 660
    float vellen; // 668
    bool onground; // 672
    bool onladder; // 673 - its ok
    bool last_onground; // 674
    bool last_onladder; // 675
    bool onwall; // 676
    bool catapult_shot; // 677
    bool onclimb; // 678
	
	// ------ edited 
	bool stupidshit;
	// ------ edited 
	
    Vec2f groundnormal; // 680
    int jumpcount; // 688 - its ok
    int aircount; // 692
    Vec2f aimpos; // 696
    Vec2f tileaimpos; // 704
    bool crouch; // 712 - its ok
    bool shield_up; // 713 - its ok
    bool shield_side; // 714
    bool shield_down; // 715 - its ok
    bool building; // 716   
    float maxvspeed; // 717
    float maxhspeed; // 721
    float gravity; // 725
	
	// ------ edited 
	char blahblah1;
	char blahblah2;
	char blahblah3;
	// ------ edited 
	
    bool onshield; // 729
    bool key_up; // 733 - its ok
    bool key_down; // 734
    bool key_left; // 735
    bool key_right; // 736
    bool key_action; // 737
    bool key_action2; // 738
    bool key_zoomin; // 739
    bool key_zoomout; // 740
    bool key_use; // 741
    bool key_change; // 742
    bool key_drop; // 743
    bool key_taunts; // 744
    bool key_bubbles; // 745
    bool key_menu; // 746
    bool key_party; // 747 -  its ok
    bool old_key_down; // 748
    bool old_key_up; // 749
    bool old_key_action; // 750
    bool old_key_action2; // 751
    bool old_key_zoomin; // 752
    bool old_key_zoomout; // 753
    bool old_key_take; // 754
    bool old_key_change; // 755
    bool old_key_drop; // 756
    bool old_key_bubbles; // 757
    bool old_key_taunts; // 758
    bool old_key_menu; // 759
    bool old_key_party; // 760 - its ok
    bool didtake; // 761
	
	// ------ edited
	char someshit1;
	char someshit2;
	// ------ edited 
	
    unsigned int bubble; // 764
    unsigned int cursor; // 768
    unsigned int indicator; // 772
    char showbubble; //776 - its ok
	
	// ------ edited
	char wtfisthis1;
	char wtfisthis2;
	char wtfisthis3;
	// ------ edited 
	
    int bubbletime; // 780
    int cursor_frame; // 784
    unsigned int headsprite; // 788
    int head_emotion; // 792
    int head_frame; // 796
    char resources[5]; // 800 - its ok
    char max_capacity; // 805
    unsigned int carry_egg; // 806
	
	// edited
	unsigned int aaaaaaa; // 810
	unsigned int bbbbbbb; // 814
	unsigned int ccccccc; // 818
	unsigned int ddddddd; // 822
	unsigned int eeeeeee; // 826
	char ffffff; // 830
	char gggggg; // 831
	// edited

    //irr::core::array<CRunner::BuildTile*, irr::core::irrAllocator<CRunner::BuildTile*> > buildtiles; // 824 - for sure, to chyba zajmuje 8 bajtow
    unsigned int collidingActor; // 832
    int picksound_time; // 836
    unsigned int bowpull; // 840
    bool cursorclose; // 844
    bool buildable; // 845
    bool can_physics_build; // 846
    bool gibbed; // 847
    bool death_screamed; // 848
    bool hitactor; // 849
	char dfdfd1;
	char dfdfd2;
    int lastspikehit; // 852
    int last_resources_added; // 856
    bool ontent; // 860
	char asdads1;
	char asfgds2;
	char dsgsgs3;
    int time_since_spawn; // 864
    int thrown_out_mats; // 868
    unsigned int collides_catapult; // 872
    unsigned int old_collides_catapult; // 876
    int lastbuildoffset; // 880
    int lastcoinsamount; // 884
    unsigned int talksound; // 888
    unsigned int usemenu; // 892
    unsigned int itemmenu;
    unsigned int miscmenu;
    unsigned int partymenu;
    unsigned int chatmenu;
    unsigned int bubblemenu;
};