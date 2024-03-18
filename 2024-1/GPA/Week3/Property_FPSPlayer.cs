class FPSPlayer {
    // 클래스 내부 필드
    private string _name;
    private float _atk;
    private float _def;
    private int _hp;
    private int _level;
    
    /// <summary>
    /// 플레이어명
    /// </summary>
    /// <exception cref="ArgumentOutOfRangeException">설정값이 "RPGPlayer"인 경우 발생</exception>
    public string Name {
        get => _name;
        set {
            if(value.Equals("RPGPlayer"))
                throw new ArgumentOutOfRangeException(nameof(value), "Name is invalid");
            
            _name = value;
        }
    }

    /// <summary>
    /// 공격력
    /// </summary>
    /// <exception cref="ArgumentOutOfRangeException">설정값이 0 미만 또는 1000 초과인 경우 예외 발생</exception>
    public float Atk {
        get => _atk;
        set {
            if(value is < 0 or > 1000)
                throw new ArgumentOutOfRangeException(nameof(value), "Atk is out of range");
            
            _atk = value;
        }
    }
    
    /// <summary>
    /// 방어력
    /// </summary>
    /// <exception cref="ArgumentOutOfRangeException">설정값이 0 미만 또는 500 초과인 경우 예외 발생</exception>
    public float Def {
        get => _def;
        set {
            if(value is < 0 or > 500)
                throw new ArgumentOutOfRangeException(nameof(value), "Def is out of range");
            
            _def = value;
        }
    }
    
    /// <summary>
    /// 체력
    /// </summary>
    /// <exception cref="ArgumentOutOfRangeException">설정값이 0 미만 또는 100,000 초과인 경우 예외 발생</exception>
    public int HP {
        get => _hp;
        set {
            if(value is < 0 or > 100_000)
                throw new ArgumentOutOfRangeException(nameof(value), "HP is out of range");
            
            _hp = value;
        }
    }
    
    /// <summary>
    /// 레벨
    /// </summary>
    /// <exception cref="ArgumentOutOfRangeException">설정값이 0 미만 또는 100 초과인 경우 예외 발생</exception>
    public int Level {
        get => _level;
        set {
            if(value is < 0 or > 100)
                throw new ArgumentOutOfRangeException(nameof(value), "Level is out of range");
            
            _level = value;
        }
    }

    /// <summary>
    /// 플레이어 정보를 콘솔에 출력
    /// </summary>
    public void Print() {
        Console.WriteLine($"Name: {_name}");
        Console.WriteLine($"Atk: {_atk}");
        Console.WriteLine($"Def: {_def}");
        Console.WriteLine($"HP: {_hp}");
        Console.WriteLine($"Level: {_level}");
    }
    
    /// <summary>
    /// 과제용 테스트 함수
    /// </summary>
    public static void Example() {
        // 정상 입력 테스트
        var player = new FPSPlayer {
            Name = "FPSPlayer",
            Atk = 100,
            Def = 50,
            HP = 1000,
            Level = 10
        };
        player.Print();
        
        // 예외 발생 테스트
        try {
            player.Name = "RPGPlayer";
        } catch(Exception e) {
            Console.WriteLine(e.Message);
        }

        try {
            player.Atk = 1001;
        } catch(Exception e) {
            Console.WriteLine(e.Message);
        }
        
        try {
            player.Def = 501;
        } catch(Exception e) {
            Console.WriteLine(e.Message);
        }
        
        try {
            player.HP = 100_001;
        } catch(Exception e) {
            Console.WriteLine(e.Message);
        }
        
        try {
            player.Level = 101;
        } catch(Exception e) {
            Console.WriteLine(e.Message);
        }
    }
}
