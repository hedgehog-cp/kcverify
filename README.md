# kcverify

# Development

1. サブモジュールを含めてクローンします.

    ```
    git clone --recurse ${url}
    ```

2. ビルドをします.

    まず, ディレクトリに移動します.

    ```
    cd /PATH/TO/kcverify
    ```

    次にマスタデータを更新します.  
    マスタデータは74式ENの`ツール`->{`艦船図鑑`, `装備図鑑`}->`ファイル`->`CSV出力(データ用)`から取得します.  
    `ファイル`->`設定`->`ログ`から文字コードを`UTF-8`または`UTF-8(BOM)`にして出力してください.  
    出力した艦船および装備のマスタをヘッダファイルに埋め込みます.

    ```
    chmod +x ./preprocess.sh
    ./preprocess.sh
    ```

    そして, ビルドを開始します.  
    C++23で書いています.  
    GCC14以上またはclang18以上, あるいはこれらに相当するコンパイラを利用してください.

    ```
    mkdir build && cd build
    cmake ..
    cmake --build . --parallel
    ```
