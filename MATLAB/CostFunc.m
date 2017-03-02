function z = CostFunc(x,mousePos)
         
        x = x - mousePos;
        z = sum(x.^2);

end