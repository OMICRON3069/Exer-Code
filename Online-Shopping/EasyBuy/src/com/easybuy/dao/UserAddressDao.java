package com.easybuy.dao;

import com.easybuy.entity.UserAddress;
import com.easybuy.param.UserAddressParam;

import java.util.List;

public interface UserAddressDao {
    List<UserAddress> queryUserAddressList(UserAddressParam param);
    
    Integer add(UserAddress userAddress);
    
    UserAddress getUserAddressById(Integer addressId);
}
