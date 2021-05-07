pragma solidity ^0.5.0;

contract TiaoSao{
    
    string public name;
    uint public productCount = 0;
    mapping (uint => Product) public products;
    
    struct Product{
        
        uint id;
        string name;
        string description;
        uint price;
        address payable owner;
        bool purchased;
        
    }
    //原来以为Xchain会有响应的 
    event ProductCreated(
        uint id,
        string name,
        string description,
        uint price,
        address payable owner,
        bool purchased
        );

    event ProductPurchased(
        uint id,
        string name,
        string description,
        uint price,
        address payable owner,
        bool purchased
        );
    
    
    constructor() public {
        name= "-----HITSZ Flea Market-----";
    }  //constructor is NO return 
    
    
    function createProduct(string memory _name , string memory _description,uint _price) public {
    
        //确保合法
        if(bytes(_name).length <= 0)
            revert("Product's name's length should be positive!");
        if(bytes(_description).length <= 0)
            revert("Product's description's length should be positive!");
        if(_price <= 0)
            revert("Product's price should be positive!");
        productCount++;
        //创建一个产品
        products[productCount] = Product(productCount,_name,_description,_price,msg.sender,false);
        emit ProductCreated(productCount,_name,_description,_price,msg.sender,false);
    }
    
    
    function purchaseProduct(uint _id) public payable {
        
        Product memory _product = products[_id];
        address payable _seller = _product.owner;
        //make sure that...
        if(_product.id < 0 || _product.id > productCount)
            revert("Product's id should bewteen 1~productCount!");
        if(msg.value < _product.price)
            revert("Fee not enough!");
        if(_product.purchased)
            revert("This Product has been purchased!");
        if(_seller == msg.sender)
            revert("You can't buy your own products!");
        
        _product.owner = msg.sender;
        _product.purchased = true;
        
        //update the imformation of products
        products[_id]= _product;
        address(_seller).transfer(msg.value);
        emit ProductPurchased(productCount,_product.name,_product.description,_product.price,msg.sender,true);
    }
    
    function getAllProductBrief() view public returns(string memory){
        
        string memory res = "-----HITSZ Flea Market";
        
        for(uint i=1;i<=productCount;i++){
            res=string(abi.encodePacked (res,"-----NO",uint2str(i),":","[Name]:",products[i].name,", [Price]:",uint2str(products[i].price),", [State]:",boolstr(products[i].purchased)));
        }
        return res;
        
    }  //No description
    
    
    function getAllProductDes() view public returns(string memory){
        
       string memory res = "-----HITSZ Flea Market";
        
        for(uint i=1;i<=productCount;i++){
            res=string(abi.encodePacked (res,"-----NO",uint2str(i),":","[Name]:",products[i].name,", Description]:",products[i].description,", [Price]:",uint2str(products[i].price),", [State]:",boolstr(products[i].purchased)));
        }
        return res;
    }
    
    
    
    function getUnpurchasedProduct() view public returns(string memory){
        string memory res = "---*Unpurchased Products:*";
        uint i =1;
        uint j=1;
        while(j<=productCount){
            if(!products[j].purchased){
                res=string(abi.encodePacked (res,"-----NO",uint2str(j),":","[Name]:",products[j].name,", [Price]:",uint2str(products[j].price) ));
                i++;
            }
            j++;
        }
        if(i == 1)
            return "No Unpurchased Products";
        return res;
    }
    
    
    
    function getPurchasedProduct()view public returns(string memory){
        string memory res = "---*Purchased Products:*";
        uint i =1;
        uint j=1;
        while(j<=productCount){
            if(products[j].purchased){
                res=string(abi.encodePacked (res,"-----NO",uint2str(j),":","[Name]:",products[j].name,", [Price]:",uint2str(products[j].price) ));
                i++;
            }
            j++;
        }
        if(i == 1)
            return "No Purchased Products";
        return res;
    }
    
    
    function undercarriage(uint _id) public returns (string memory){
        if(products[_id].owner == msg.sender)
        {
            for(uint i = _id;i <productCount;i++){
                products[i]=products[i+1];
            }
            productCount--;
            return "Product has been undercarriaged";
        }
        else
            return "You are not the owner!";
        
        
    }
    
    //function getSeller()
    
     function uint2str(uint _i) internal pure returns (string memory _uintAsString) {
        if (_i == 0) {
            return "0";
        }
        uint j = _i;
        uint len;
        while (j != 0) {
            len++;
            j /= 10;
        }
        bytes memory bstr = new bytes(len);
        uint k = len;
        while (_i != 0) {
            k = k-1;
            uint8 temp = (48 + uint8(_i - _i / 10 * 10));
            bytes1 b1 = bytes1(temp);
            bstr[k] = b1;
            _i /= 10;
        }
        return string(bstr);
    }
    
    function boolstr(bool _i) internal pure returns (string memory){
        if (_i == false)
            return "Unpurchased";
        else
            return "Purchased";
    }
    
    
     function char(bytes1 b) internal pure returns (bytes1 c) {
        if (uint8(b) < 10) return bytes1(uint8(b) + 0x30);
        else return bytes1(uint8(b) + 0x57);
    }

}
