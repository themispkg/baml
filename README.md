# baml 1.0.0
baml ain't markup language

# installation
```
git clone https://github.com/themispkg/baml.git ; cd baml && sudo make install
```

# usage (as script):
```bash
#!/bin/bash

# source the baml file, if you already installed it you can type 'source baml'
source ./"baml.sh"

baml:parse2bash "./example.baml"
```
the output:
![image](https://user-images.githubusercontent.com/54551308/149844992-1e1ac159-d14d-4290-808e-6fc3949fdc02.png)

# baml file (example.baml):
```
test;
    -> deneme1
    -> deneme2
    -> 123

deneme123;
    -> tamam bu
    -> oldu
```

# NOT
also you can change the **ARGUMENT TOKEN** and the **ARRAY TOKEN** as you want
![image](https://user-images.githubusercontent.com/54551308/149845231-6168ebde-2344-45c5-bd54-0dfe6299bb14.png)

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please test with shellcheck before open pull request.

## License
[GPL3](https://choosealicense.com/licenses/gpl-3.0/)
