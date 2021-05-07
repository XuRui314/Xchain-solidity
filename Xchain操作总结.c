/*-----创建文件夹/文件-----*/

创建文件夹：mkdir <文件夹名>   ep:mkdir test
创建文件：touch <文件名>    ep:touch test.sol




/*-----添加环境变量的两种方法-----*/
一.直接在当前目录下添加变量，生存期仅限于此终端
export PATH=${PATH}:`pwd`

二.一劳永逸的方法，在配置文件中永久添加环境变量
sudo gedit ~/.bashrc  //先打开配置文件
然后在最后加上
export PATH=路径名:$PATH
给个例子，路径名可以在目录下直接输入pwd获取
export PATH=/xuperchain/core/contractsdk/evm/example/counter:$PATH

/*-----solc-select 更改solc版本操作-----*/

https://github.com/crytic/solc-select

看文档






代理下载前面加上
GOPROXY=goproxy.cn

/*-----合约实战-----*/
编译合约
solc --bin --abi market.sol -o .
部署合约
./xchain-cli evm deploy --account XC1111111111111111@xuper --cname fleamarketevm --fee 520000 ../../xuperchain/core/contractsdk/Xchain-HITSZ-flea/TiaoSao.bin --abi ../../xuperchain/core/contractsdk/Xchain-HITSZ-flea/TiaoSao.abi -H:39101

/*-------
||调用合约||
---------*/

//第一种是不需要fee的
无参数
./xchain-cli evm query --method getName -a '{"0":""}' Helloworldevm --abi Helloworld.abi -H:39101 --name xuper

有参数："形参":"实参"  的格式
./xchain-cli evm query --method testPure -a '{"a":"5","b":"7"}' Helloworldevm --abi Helloworld.abi -H:39101 --name xuper
./xchain-cli evm query --method candidates -a '{"":"0"}' movievoteevm --abi MovieBallot.abi -H:39101 --name xuper

//第二种是需要fee的，method就是函数，然后传参就是形参+实参
./xchain-cli evm invoke --method changeName -a '{"_name":"TsingHua"}' Helloworldevm --fee 222 --abi Helloworld.abi -H:39101 --name xuper
./xchain-cli evm invoke --method voteCandidates -a '{"index":"0"}' movievoteevm --fee 52000 --abi MovieBallot.abi -H:39101 --name xuper



/*------------------分割线-------------------*/
//出售商品，如果输入错误会进行不同的报错
./xchain-cli evm invoke --method createProduct -a '{"_name":"iPhone 12 purple","_description":"9.5New with a little damage on the back","_price":"5300"}' fleamarketevm --fee 52000 --abi TiaoSao.abi -H:39101 --name xuper

./xchain-cli evm invoke --method createProduct -a '{"_name":"iPad Air 4","_description":"9New,used for 10 months,Just used for noting and studying","_price":"4000"}' fleamarketevm --fee 52000 --abi TiaoSao.abi -H:39101 --name xuper

./xchain-cli evm invoke --method createProduct -a '{"_name":"AirPods Pro","_description":"9.9New,just open for checking,never uses","_price":"1500"}' fleamarketevm --fee 52000 --abi TiaoSao.abi -H:39101 --name xuper

//报错演示
./xchain-cli evm invoke --method createProduct -a '{"_name":"","_description":"9.5New with a little damage on the back","_price":"5300"}' fleamarketevm --fee 52000 --abi TiaoSao.abi -H:39101 --name xuper



	if(bytes(_name).length <= 0)
            revert("Product's name's length should be positive!");
        if(bytes(_description).length <= 0)
            revert("Product's description's length should be positive!");
        if(_price <= 0)
            revert("Product's price should be positive!");





xchain目前不支持公链部署evm合约,所以这部分在SolidityIDE中演示
//购买商品，如果输入错误会进行不同的报错
./xchain-cli evm invoke --method purchaseProduct -a '{"_id":"1"}' fleamarketevm --fee 52000 --amount 20000000 --abi TiaoSao.abi -H:39101 --name xuper

 	if(_product.id < 0 || _product.id > productCount)
            revert("Product's id should bewteen 1~productCount!");
        if(msg.value < _product.price)
            revert("Fee not enough!");
        if(_product.purchased)
            revert("This Product has been purchased!");
        if(_seller == msg.sender)
            revert("You can't buy your own products!");

//钱不够           
 ./xchain-cli evm invoke --method purchaseProduct -a '{"_id":"1"}' fleamarketevm --fee 52000 --amount 2 --abi TiaoSao.abi -H:39101 --name xuper            
            
            
            

查询商品
//按序号查询商品:包括商品的卖家地址
./xchain-cli evm query --method products -a '{"":"1"}' fleamarketevm --abi TiaoSao.abi -H:39101 --name xuper

//详细的商品展示，包括商品描述
./xchain-cli evm query --method getAllProductDes -a '{"0":""}' fleamarketevm --abi TiaoSao.abi -H:39101 --name xuper

//简略的商品展示
./xchain-cli evm query --method getAllProductBrief -a '{"0":""}' fleamarketevm --abi TiaoSao.abi -H:39101 --name xuper

//已经出售的商品，如果没有已出售的商品，会显示无商品出售过
./xchain-cli evm query --method getPurchasedProduct -a '{"0":""}' fleamarketevm --abi TiaoSao.abi -H:39101 --name xuper

//未出售的商品，如果商品都被买了，会显示无未出售商品
./xchain-cli evm query --method getUnpurchasedProduct -a '{"0":""}' fleamarketevm --abi TiaoSao.abi -H:39101 --name xuper

//下架商品
./xchain-cli evm invoke --method undercarriage -a '{"_id":"1"}' fleamarketevm --fee 520000 --abi TiaoSao.abi -H:39101 --name xuper



转换xchain地址为evm地址
 ./xchain-cli evm addr-trans -t x2e -f bCkKYwt2yVAuLLyGKaXVfTREtfYW1SSx

