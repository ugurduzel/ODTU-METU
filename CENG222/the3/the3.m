N = 38416;
lambda = 4;
hours = 5;

aS = 0; bS = 10;
aW = 0; bW = 10;
c = 0.2;

S = 0; W = 0; Y = c; f = 0;

inequalityHolds = zeros(N,1);
totalWeight = zeros(N,1);
expectedEstim = zeros(N,1);
eToTheMinusLambda = exp(-lambda);

for k=1:N

    numberOfMinions = 0;
    for i=1:hours
        U = rand();
        while true
            if U < eToTheMinusLambda
                break;
            end
            U = U * rand();
            numberOfMinions = numberOfMinions + 1;
        end
    end

    total = 0;
    for j=1:numberOfMinions
        while true
            U1 = rand();
            U2 = rand();
            V = rand();
            S = aS + (bS-aS)*U1;
            W = aW + (bW-aW)*U2;
            Y = c*V;
            f = S*W*exp(-S-W);
            if Y <= f
                break;
            end
        end
        if W >= 2*S
            total = total + 1;
        end
        totalWeight(k) = totalWeight(k) + W;
    end
    inequalityHolds(k) = inequalityHolds(k) + total;

    A = (-0.5) * log(rand(numberOfMinions,1));
    B = sqrt(2)*erfinv(-1+2*rand(numberOfMinions,1));
    M = (A+2*B)./(1+abs(B));
    expectedEstim(k) = mean(M);
end

Probability_Estimate = mean(inequalityHolds>6)
Weight_Estimate = mean(totalWeight)
Expected_Value_Estimate = mean(expectedEstim)
