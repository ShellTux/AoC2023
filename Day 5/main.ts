import fs from 'node:fs'
import { argv } from 'node:process'

let seeds: number[] = []

enum Map {
    NONE = 0,
    SEED_TO_SOIL = 1,
    SOIL_TO_FERTILIZER,
    FERTILIZER_TO_WATER,
    WATER_TO_LIGHT,
    LIGHT_TO_TEMPERATURE,
    TEMPERATURE_TO_HUMIDITY,
    HUMIDITY_TO_LOCATION
}

type Range = {
    destination_start: number,
    source_start: number,
    length: number
}

let seed_to_soil: Range[] = []
let soil_to_fertilizer: Range[] = []
let fertilizer_to_water: Range[] = []
let water_to_light: Range[] = []
let light_to_temperature: Range[] = []
let temperature_to_humidity: Range[] = []
let humidity_to_location: Range[] = []

let map: Map = Map.NONE
fs
    .readFileSync(argv[2], 'utf8')
    .split('\n')
    .forEach((line, lineNumber) => {
        if (line.length == 0) map++;
        if (lineNumber == 0) { // NOTE: Seeds
            seeds = line
                .split(' ')
                .slice(1)
                .map(Number)
            return
        }

        let words: String[] = line.split(' ')
        if (words.length != 3) return
        let numbers: number[] = words.map(Number)
        let range: Range = {
            destination_start: numbers[0],
            source_start: numbers[1],
            length: numbers[2],
        }


        switch (map) {
            case Map.NONE: return
            case Map.SEED_TO_SOIL: return seed_to_soil.push(range)
            case Map.SOIL_TO_FERTILIZER: return soil_to_fertilizer.push(range)
            case Map.FERTILIZER_TO_WATER: return fertilizer_to_water.push(range)
            case Map.WATER_TO_LIGHT: return water_to_light.push(range)
            case Map.LIGHT_TO_TEMPERATURE: return light_to_temperature.push(range)
            case Map.TEMPERATURE_TO_HUMIDITY: return temperature_to_humidity.push(range)
            case Map.HUMIDITY_TO_LOCATION: return humidity_to_location.push(range)
        }
    })

const map_seed = function(seed: number, maps: Range[]): number {
    for (const map of maps) {
        if (map.source_start <= seed && seed < map.source_start + map.length)
            return map.destination_start + seed - map.source_start
    }

    return seed
}

const compute_location = function(seed: number): number {
    const soil = map_seed(seed, seed_to_soil)
    const fertilizer = map_seed(soil, soil_to_fertilizer)
    const water = map_seed(fertilizer, fertilizer_to_water)
    const light = map_seed(water, water_to_light)
    const temperature = map_seed(light, light_to_temperature)
    const humidity = map_seed(temperature, temperature_to_humidity)
    const location = map_seed(humidity, humidity_to_location)
    console.log(`Seed ${seed}, soil ${soil}, fertilizer ${fertilizer},`
        + `water ${water}, light ${light},`
        + ` temperature ${temperature}, humidity ${humidity}, location ${location}.`)
    return location
}

const min_location: number = seeds
    .map(compute_location)
    .reduce((min, current) => Math.min(min, current), Infinity);

console.log(`\nLowest location: ${min_location}.`)
