"""
IP address - 4 8 bits = 32 bits
subnet mask = 4 8 bits = 32 bits
subnet mask seperates the network portion and the host portion of an IP address
number of 1s in subnet mask describes the number of host available to a network

"""
from numpy import prod

def printAddress(*addresses):
    for address in addresses:
        print(".".join(map(str, address)))


def getBinary(numbers):
    binary = []
    for num in numbers:
        num = bin(num)[2:]

        # turn into 8 bits
        num = (8 - len(num)) * "0" + num
        binary.append(num)
    return binary

def createSubnetMask(num=24):
    subnet = []
    while len(subnet) < 4:
        bits = "1" * 8 if num >= 8 else "1" * num + "0" * (8 - num)
        subnet.append(int(bits, 2) if num >= 0 else 0)
        num -= 8
    return subnet

def getHost(ipB, subnetB):
    host = []
    for a, b in zip(ipB, subnetB):
        newBit = a & b
        host.append(int(newBit, 2))
    return host

def getBroadcast(host, subnetB):
    magic = [2 ** bit.count("0") -1 if bit.count("0") else 0 for bit in subnetB]
    return [numHost+numMagic for numHost, numMagic in zip(host, magic)]

def getHostBits(subnetB):
    return sum([bits.count("0") for bits in subnetB])

def getAvailableHosts(hostBits):
    return 2 ** hostBits - 2

def ShowNetwork():
    ip = [int(i) for i in input("IP Address: ").split(".") if i.isdigit()]
    subnet = getSubnetMasks()[0]

    ipB = getBinary(ip)
    subnetB = getBinary(subnet)

    printAddress(ip, ipB, subnet, subnetB)

    host = getHost(ipB, subnetB)
    hostB = getBinary(host)

    printAddress(host, hostB)

    broadcast = getBroadcast(host, subnetB)
    broadcastB = getBinary(broadcast)

    printAddress(broadcast, broadcastB)

    hostBits = getHostBits(subnetB)
    availHost = getAvailableHosts(hostBits)

    print(hostBits, availHost)


# First subnet is fixed, next ones can be done to individual subnets instead.
def getSubnetMasks() -> list[str]:
    nSubnets = int(input("Number of Subnet: "))
    subnetMs = []
    while nSubnets > 0:
        subnetM = createSubnetMask(int(input("Subnet Mask: ")))
        subnetMb = getBinary(subnetM)
        if subnetMs and subnetMs[-1][1].count("0") > subnetMb.count("0"):
            subnetMs.append((subnetM, subnetMb))
            nSubnets -= 1
        else:
            print("Invalid Subnet Mask")
    return subnetMs

def getSubnets(subnetMs, ipB):
    subnets = []
    if subnets:
       for subnetM in subnetMs:
            for subnet in subnets:
                subnets.remove(subnet)
                subnetMb = getBinary(subnetM)
                subnet = getHost(subnet, subnetMb)
    else:        
        for subnetM in subnetMs:
            subnetMb = getBinary(subnetM)
            subnet = getHost(ipB, subnetMb)


def calculate_discount(amount):
    if amount <= 0:
        return 0
    elif amount <= 1000:
        return amount * 0.05
    elif amount <= 2000:
        return 1000 * 0.05 + (amount - 1000) * 0.10
    else:
        return calculate_discount(amount - 2000) + (2000) * 0.15

order_amount = 3000
print("Discount:", calculate_discount(order_amount))


# Company hierarchy as a nested dictionary


company = {
    "CEO": ["Alice", "Bob"],
    "Alice": ["Charlie", "David"],
    "Bob": [],
    "Charlie": ["Eve"],
    "David": [],
    "Eve": []
}

def count_subordinates(employee):
    if employee not in company:
        return 0
    total = 0

    queue = [employee]

    while queue:
        employee = queue.pop()
        for subordinate in company[employee]:
            total += 1 
            queue.append(subordinate)
            
    return total

# Example usage
manager = "Alice"
print(f"Total people under {manager}: {count_subordinates(manager)}")


